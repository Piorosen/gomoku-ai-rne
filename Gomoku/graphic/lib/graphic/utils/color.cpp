#include <graphic/utils/color.h>

grc::color::color()
{
    red = blue = green = alpha = 0;
}

grc::color::color(unsigned int rgba)
{
    red = (rgba >> 24) & 0xff;
    green = (rgba >> 16) & 0xff;
    blue = (rgba >> 8) & 0xff;
    alpha = (rgba >> 0) & 0xff;
}