#pragma once
#include <graphic/components/view.h>
#include <functional>

namespace grc
{
    class button : public grc::view
    {
    private:
        bool buttonKeyDown = false;

    public:
        button(grc::rect f) : grc::view(f, grc::color(0x7f7f7fff))
        {
        }

        std::function<void()> buttonDown;

        grc::color focuscolor = grc::color(0x4f4f4fff);

        virtual bool click(int state, int x, int y) override;
        virtual bool render() const override;

    protected:

    };
}