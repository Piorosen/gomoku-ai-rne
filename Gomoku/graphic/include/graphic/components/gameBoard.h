#pragma once
#include <graphic/components/view.h>
#include <functional>
#include <vector>

namespace grc
{
    class gameBoard : public grc::view
    {
    private:
        std::vector<std::vector<int>> boardState;

    public:
        int counting = 0;
        gameBoard(grc::rect f, grc::size bsize) : grc::view(f, grc::color(0x854b25ff)), boardSize(bsize)
        {
            for (int i = 0; i < boardSize.height; i++)
            {
                boardState.push_back(std::vector<int>(boardSize.width, 0));
            }
        }

        void setState(grc::point pos, int state);

        grc::size boardSize;
        grc::color lineColor = grc::color(0x36210fff);
        grc::color blackColor = grc::color(0x2f2f2fff);
        grc::color whiteColor = grc::color(0xdcdcdcff);
        grc::color predictColor = grc::color(0x0563ffff);

        // virtual int click(int state, int x, int y) override;
        virtual bool render() const override;

        void clear();

    protected:
    };
}