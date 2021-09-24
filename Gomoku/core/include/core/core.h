#pragma once
#include "AI.h"

#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <functional>

#include <rapidjson/document.h>

namespace core
{
    enum class color : int
    {
        black = 0,
        white = 1,
        none = 2,
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
        std::function<std::vector<core::scorePoint>(core::color, std::vector<std::vector<core::color>>)> notFoundAi;
        int defaultAiCalcTime = 500;

        int boardSize = 15;

    public:
        AI wine;

        core::node root;
        static std::unique_ptr<core::ai> shared;

        // default : 500ms
        void setDefaultAiCalculateTimeOut(int milliseconds);
        void setNotFoundAi(std::vector<core::scorePoint> (*sudoAi)(core::color, std::vector<std::vector<core::color>>));
        void setNotFoundAi(std::function<std::vector<core::scorePoint>(core::color, std::vector<std::vector<core::color>>)> sudoAi);

        std::vector<core::scorePoint> getNextNode(core::sqeuence seqeuence);
        void newAI(std::string path);
        void loadAI(std::string path);
        void saveAI(std::string path);

        void appendAI(core::sqeuence sequence, core::color winner, double discountRate = 0.5);
    };
}