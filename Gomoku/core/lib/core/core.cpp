#include <core/core.h>

#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

#include <spdlog/spdlog.h>

std::unique_ptr<core::ai> core::ai::shared = std::make_unique<core::ai>();

std::vector<core::node> core::ai::getNextNode(core::sqeuence sequence) const
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

        node = &node->next[idx];
    }
    return node->next;
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
        // 없음
        if (idx == -1)
        {
            core::node n;
            // 0 승리 -> 흑
            // 0 2 4 6
            // 짝수 == 흑
            // 홀수 == 백
            // sequenceIndex % 2 == winner +
            // != -
            // pow(discountRate, sequence.size() - sequenceIndex - 1)
            n.score = std::pow(discountRate, sequence.size() - seqIdx - 1) * (seqIdx % 2 == (int)winner ? +1 : -1);
            n.point = seq;
            node->next.push_back(n);

            node = &node->next[node->next.size() - 1];
        }
        // 있음
        else
        {
            auto score = std::pow(discountRate, sequence.size() - seqIdx - 1) * (seqIdx % 2 == (int)winner ? +1 : -1);
            node->next[idx].score += score;

            node = &node->next[idx];
        }
    }
}