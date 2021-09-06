#pragma once
#include <memory>
#include <string>
#include <vector>

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

    using sqeuence = std::vector<point>;

    struct node
    {
        std::vector<std::unique_ptr<node>> next;

        core::point point = {0, 0};
        double score = 0;
    };

    class ai
    {
    private:
    public:
        static std::unique_ptr<core::ai> shared;

        void newAI(std::string path);
        void loadAI(std::string path);
        void saveAI(std::string path);

        void appendAI(core::sqeuence sequence, core::color winner);
    };
}