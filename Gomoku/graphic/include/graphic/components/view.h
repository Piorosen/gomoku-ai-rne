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
    public:
        view(grc::rect f, grc::color b)
        {
            frame = f;
            background = b;
        }

        grc::rect frame;
        grc::rect bounds;

        grc::color background;

        std::vector<std::shared_ptr<grc::view>> controls;

        virtual void render() const;

    protected:
    };
}