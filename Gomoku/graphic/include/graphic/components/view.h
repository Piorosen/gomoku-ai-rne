#pragma once
#include <graphic/utils/rect.h>
#include <graphic/utils/color.h>

#include <vector>
#include <memory>

namespace grc
{
    class view
    {
    private:
        std::vector<std::shared_ptr<grc::view>> controls;

    public:
        view(grc::rect f, grc::color b)
        {
            frame = f;
            background = b;
        }

        grc::rect frame;
        grc::color background;

        virtual void render() const;

    protected:
    };
}