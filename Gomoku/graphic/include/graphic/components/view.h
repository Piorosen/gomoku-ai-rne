#pragma once
#include <graphic/utils/rect.h>
#include <graphic/utils/color.h>

#include <string>
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

        std::vector<std::shared_ptr<grc::view>> controls;
        grc::rect frame;
        grc::color background;

        void setHidden(bool value);
        bool getHidden() const;

        void setBorder(int borderSize, grc::color borderColor = grc::color(0xffffffff));

        virtual bool render() const;
        virtual int click(int state, int x, int y);

    protected:
        bool isHidden = false;
        int borderSize = 0;
        grc::color borderColor = grc::color(0xffffffff);

        bool propagation() const;

        void drawRect(grc::rect size, grc::color color = grc::color(0xffffffff)) const;
        void drawCircle(grc::point pt, float radius, grc::color color) const;
        void drawLine(grc::point x, grc::point y, float thin = 5, grc::color color = grc::color(0xffffffff)) const;
        void drawImage(grc::rect size, unsigned int imageId) const;
        void drawBitmapText(std::string text, grc::point pos) const;
    };
}