#pragma once
#include "AI.h"

#include <memory>
#include <string>
#include <vector>
#include <optional>

#include <rapidjson/document.h>

namespace core
{
    enum class color : int
    {
        black = 0,
        white = 1
    };

    struct point
    {
        int x, y;
    };

    struct node
    {
        std::vector<node> next;

        core::point point = {0, 0};
        double score = 0;
    };

    struct scorePoint
    {
        core::point point = {0, 0};
        double score = 0;
    };

    using sqeuence = std::vector<core::point>;

    class ai
    {
    private:
        core::node getNode(rapidjson::Value &data);

    public:
        AI wine;

        core::node root;
        static std::unique_ptr<core::ai> shared;

        std::vector<core::scorePoint> getNextNode(core::sqeuence seqeuence);
        void newAI(std::string path);
        void loadAI(std::string path);
        void saveAI(std::string path);

        void appendAI(core::sqeuence sequence, core::color winner, double discountRate = 0.5);
    };
}