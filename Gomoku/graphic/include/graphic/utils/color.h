#pragma once

namespace grc
{
    struct color
    {
        unsigned char red, blue, green, alpha = 0;

        color();
        color(unsigned int rgba);
    };

}