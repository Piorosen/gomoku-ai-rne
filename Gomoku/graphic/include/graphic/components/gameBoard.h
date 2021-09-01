#pragma once
#include <graphic/components/view.h>
#include <functional>

namespace grc
{
    class gameBoard : public grc::view
    {
    private:
    public:
        gameBoard(grc::rect f) : grc::view(f, grc::color(0x885000ff))
        {
        }

        grc::size boardSize = {13, 13};
        grc::color lineColor = grc::color(0xffffffff);
        grc::color blackColor = grc::color(0x2f2f2fff);
        grc::color whiteColor = grc::color(0xdcdcdcff);
        grc::color predictColor = grc::color(0xefef99ff);

        virtual int click(int state, int x, int y) override;
        virtual bool render() const override;

    protected:
    };
}