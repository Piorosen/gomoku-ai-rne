#pragma once

namespace grc
{
    struct color
    {
        unsigned char red, blue, green, alpha = 0;

        color()
        {
            red = blue = green = alpha = 0;
        }

        color(unsigned int rgba)
        {
            red = (rgba >> 24) & 0xff;
            blue = (rgba >> 16) & 0xff;
            green = (rgba >> 8) & 0xff;
            alpha = (rgba >> 0) & 0xff;
        }
    };

}