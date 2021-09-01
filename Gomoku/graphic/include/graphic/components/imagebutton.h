#pragma once
#include <graphic/components/view.h>
#include <optional>

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

        std::optional<unsigned int> backgroundImageId = std::nullopt;
        std::optional<unsigned int> focusImageId = std::nullopt;

        virtual bool click(int state, int x, int y) override;
        virtual void render() const override;

    protected:

    };
}