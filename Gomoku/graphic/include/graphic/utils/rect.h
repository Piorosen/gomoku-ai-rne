#pragma once
#include <graphic/utils/point.h>
#include <graphic/utils/size.h>

namespace grc
{
    struct rect
    {
        grc::point location;
        grc::size size;

        grc::point center() const
        {
            return {location.x + (size.width / 2), location.y + (size.height / 2)};
        }
    };

}