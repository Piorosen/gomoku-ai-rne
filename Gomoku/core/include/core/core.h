#pragma once
#include <memory>
#include <string>
#include <vector>
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

    using sqeuence = std::vector<core::point>;

    class ai
    {
    private:
        core::node getNode(rapidjson::Value &data);

    public:
        core::node root;
        static std::unique_ptr<core::ai> shared;

        std::vector<core::node> getNextNode(core::sqeuence seqeuence) const;
        void newAI(std::string path);
        void loadAI(std::string path);
        void saveAI(std::string path);

        void appendAI(core::sqeuence sequence, core::color winner, double discountRate = 0.5);
    };
}