#pragma once
#define GL_SILENCE_DEPRECATION

#include <graphic/components/view.h>
#include <graphic/utils/color.h>
#include <graphic/utils/rect.h>
#include <optional>

namespace grc
{
    class imageview : public grc::view
    {
    private:
    public:
        imageview(grc::rect f) : grc::view(f, grc::color(0xff3f3fff))
        {
        }
        imageview(grc::rect f, grc::color c) : grc::view(f, grc::color(0xff3f3fff))
        {
        }

        virtual bool render() const override;
        std::optional<unsigned int> imageId = std::nullopt;

    protected:
        

    };
}