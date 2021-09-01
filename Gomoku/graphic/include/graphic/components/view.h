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

        void setHidden(bool value);
        bool getHidden() const;

        virtual bool render() const;
        virtual bool click(int state, int x, int y);

    protected:
        bool isHidden = false;

        void drawRect(grc::rect size, grc::color color = grc::color(0xffffffff)) const;
        void drawCircle(grc::point pt, float radius, grc::color color) const;
        void drawLine(grc::point x, grc::point y, float thin = 5, grc::color color = grc::color(0xffffffff)) const;
        void drawImage(grc::rect size, unsigned int imageId) const;
    };
}