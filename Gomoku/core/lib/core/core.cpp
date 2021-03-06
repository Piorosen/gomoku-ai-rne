#include <core/core.h>

#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

#include <spdlog/spdlog.h>

std::unique_ptr<core::ai> core::ai::shared = std::make_unique<core::ai>();

void core::ai::setDefaultAiCalculateTimeOut(int milliseconds)
{
    this->defaultAiCalcTime = milliseconds;
}

void core::ai::setNotFoundAi(std::vector<core::scorePoint> (*sudoAi)(core::color, std::vector<std::vector<core::color>>))
{
    this->notFoundAi = sudoAi;
}
void core::ai::setNotFoundAi(std::function<std::vector<core::scorePoint>(core::color, std::vector<std::vector<core::color>>)> sudoAi)
{
    this->notFoundAi = sudoAi;
}

std::vector<core::scorePoint> core::ai::getNextNode(core::sqeuence sequence)
{
    spdlog::info("time get Next Node");

    auto *node = &this->root;

    int idx = 0;
    for (int seqIdx = 0; seqIdx < sequence.size(); seqIdx++)
    {
        auto seq = sequence[seqIdx];
        idx = -1;
        for (int i = 0; i < node->next.size(); i++)
        {
            if (node->next[i].point.x == seq.x && node->next[i].point.y == seq.y)
            {
                idx = i;
                break;
            }
            else
            {
                continue;
            }
        }

        if (idx == -1)
        {
            spdlog::critical("not found next Node");
            break;
            // return std::vector<core::scorePoint>();
        }
        else
        {
            node = &node->next[idx];
        }
    }
    spdlog::info("time get Next Node retuning");

    std::vector<core::scorePoint> pt;

    if (idx != -1)
    {
        for (auto &node : node->next)
        {
            pt.push_back({{node.point.x, node.point.y}, node.score});
        }
    }

    spdlog::info("pt size : [{}]", pt.size());
    if (pt.size() == 0)
    {
        if (this->notFoundAi)
        {
            spdlog::info("find : user ai");
            std::vector<std::vector<core::color>> boardState;

            // init
            for (int y = 0; y < boardSize; y++)
            {
                std::vector<core::color> line;

                for (int x = 0; x < boardSize; x++)
                {
                    line.push_back(core::color::none);
                }
                boardState.push_back(line);
            }

            for (int seq = 0; seq < sequence.size(); seq++)
            {
                auto &p = sequence[seq];
                boardState[p.y][p.x] = seq % 2 == 0 ? core::color::black
                                                    : core::color::white;
            }

            auto userai = notFoundAi(sequence.size() % 2 == 0 ? core::color::black
                                                              : core::color::white,
                                     boardState);

            pt.insert(pt.end(), userai.begin(), userai.end());
        }

        if (pt.size() == 0)
        {
            spdlog::info("not find : user ai");

            wine.ReStart();
            wine.timeout_turn = defaultAiCalcTime;

            for (auto &p : sequence)
            {
                Pos pos;
                pos.x = p.x + 1;
                pos.y = p.y + 1;
                wine.PutChess(pos);
            }

            Pos best = wine.GetBestMove();
            core::scorePoint pts;
            pts.score = 1;
            pts.point.x = best.x - 1;
            pts.point.y = best.y - 1;

            pt.push_back(pts);
        }
    }

    spdlog::info("----- Search Ai Result -----");
    std::sort(pt.begin(), pt.end(), [](core::scorePoint &a, core::scorePoint &b)
              { return a.score > b.score; });
    for (int i = 0; i < pt.size(); i++)
    {
        spdlog::info("{} : Score : {:.5} \t\t : [{}, {}]", i + 1, pt[i].score, pt[i].point.x, pt[i].point.y);
    }
    return pt;
}

void core::ai::newAI(std::string path)
{
}

core::node core::ai::getNode(rapidjson::Value &data)
{
    core::node n;

    n.score = data["score"].GetDouble();
    auto pos = data["pt"].GetInt();
    n.point = {pos / 100, pos % 100};

    for (auto &item : data["node"].GetArray())
    {
        n.next.push_back(getNode(item));
    }

    return n;
}

void core::ai::loadAI(std::string path)
{
    wine.SetSize(boardSize);

    spdlog::info("ai load start : [{}]", path);
    std::ifstream f(path);

    std::ostringstream ss;
    ss << f.rdbuf();
    std::string str = ss.str();

    f.close();

    rapidjson::Document d;
    d.Parse(str.c_str());

    if (d.HasParseError())
    {
        spdlog::info("core : pre learner load fail [{}]", path);
    }
    spdlog::info("ai parisng finished : [{}]", path);

    for (auto &item : d.GetArray())
    {
        this->root.next.push_back(getNode(item));
    }

    spdlog::info("ai load finished : [{}]", path);
}

void core::ai::saveAI(std::string path)
{
}

void core::ai::appendAI(core::sqeuence sequence, core::color winner, double discountRate)
{
    auto *node = &this->root;

    for (int seqIdx = 0; seqIdx < sequence.size(); seqIdx++)
    {
        auto seq = sequence[seqIdx];
        int idx = -1;
        for (int i = 0; i < node->next.size(); i++)
        {
            if (node->next[i].point.x == seq.x && node->next[i].point.y == seq.y)
            {
                idx = i;
                break;
            }
            else
            {
                continue;
            }
        }
        // ??????
        if (idx == -1)
        {
            core::node n;
            // 0 ?????? -> ???
            // 0 2 4 6
            // ?????? == ???
            // ?????? == ???
            // sequenceIndex % 2 == winner +
            // != -
            // pow(discountRate, sequence.size() - sequenceIndex - 1)
            n.score = std::pow(discountRate, sequence.size() - seqIdx - 1) * (seqIdx % 2 == (int)winner ? +1 : -1);
            n.point = seq;
            node->next.push_back(n);

            node = &node->next[node->next.size() - 1];
        }
        // ??????
        else
        {
            auto score = std::pow(discountRate, sequence.size() - seqIdx - 1) * (seqIdx % 2 == (int)winner ? +1 : -1);
            node->next[idx].score += score;

            node = &node->next[idx];
        }
    }
}