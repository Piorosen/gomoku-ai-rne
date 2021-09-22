#pragma once
#define GL_SILENCE_DEPRECATION

#include <graphic/components/view.h>
#include <graphic/utils/color.h>
#include <graphic/utils/rect.h>
#include <optional>

namespace grc
{
    class popupview : public grc::view
    {
    private:
    public:
        enum class direction : int
        {
            leftTop,
            rightTop,
            leftBottom,
            rightBottom
        };

        popupview(grc::rect f) : grc::view(f, grc::color(0xff3f3fff))
        {
        }
        popupview(grc::rect f, grc::color c) : grc::view(f, grc::color(0xff3f3fff))
        {
        }

        virtual bool render() const override;

    protected:
    };
}