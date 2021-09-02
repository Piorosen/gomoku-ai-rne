#pragma once
#include <graphic/components/view.h>
#include <optional>
#include <functional>

namespace grc
{
    class imagebutton : public grc::view
    {
    private:
        bool buttonKeyDown = false;

    public:
        imagebutton(grc::rect f) : grc::view(f, grc::color(0x7f7f7fff))
        {
        }

        std::function<void()> buttonDown;

        std::optional<unsigned int> backgroundImageId = std::nullopt;
        std::optional<unsigned int> focusImageId = std::nullopt;

        virtual int click(int state, int x, int y) override;
        virtual bool render() const override;

    protected:
    };
}