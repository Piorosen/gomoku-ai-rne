#include <core/core.h>
#include <algorithm>
#include <cmath>

std::unique_ptr<core::ai> core::ai::shared = std::make_unique<core::ai>();

std::vector<core::node> core::ai::getNextNode(core::sqeuence sequence) const
{
    auto *node = &this->root;

    for (int seqIdx = 0; seqIdx < sequence.size(); seqIdx++)
    {
        auto seq = sequence[seqIdx];
        auto ret = std::find_if(node->next.begin(), node->next.end(), [&seq](core::node item)
                                {
                                    if (item.point.x == seq.x && item.point.y == seq.y)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                });

        auto index = (ret - node->next.begin());

        node = &node->next[index];
    }
    return node->next;
}

void core::ai::newAI(std::string path)
{
}

void core::ai::loadAI(std::string path)
{
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
        auto ret = std::find_if(node->next.begin(), node->next.end(), [&seq](core::node item)
                                {
                                    if (item.point.x == seq.x && item.point.y == seq.y)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                });
        // 없음
        if (ret == node->next.end())
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
            auto index = (ret - node->next.begin());
            auto score = std::pow(discountRate, sequence.size() - seqIdx - 1) * (seqIdx % 2 == (int)winner ? +1 : -1);
            node->next[index].score += score;

            node = &node->next[index];
        }
    }
}