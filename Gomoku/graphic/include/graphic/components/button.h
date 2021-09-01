#pragma once
#include <graphic/components/view.h>

namespace grc
{
    class button : public grc::view
    {
    private:
        bool buttonKeyDown = false;

    public:
        button(grc::rect f) : grc::view(f, grc::color(0xff0000ff))
        {
        }

        grc::color focuscolor = grc::color(0xffff00ff);

        virtual bool click(int state, int x, int y) override;
        virtual void render() const override;

    protected:

    };
}