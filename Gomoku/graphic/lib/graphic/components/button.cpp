#define GL_SILENCE_DEPRECATION

#include <graphic/components/button.h>
#include <glut.h>

bool grc::button::click(int state, int x, int y) { 
    auto r = grc::view::click(state, x, y);

    if (this->buttonKeyDown) {
        if (state == 1) {
            if (r && buttonDown)
            {
                buttonDown();
            }
            this->buttonKeyDown = false;
            glutPostRedisplay();
        }
    }else if (!this->buttonKeyDown && r) {
        if (state == 0) {
            this->buttonKeyDown = true;
            glutPostRedisplay();
        }
    }

    return r;
}

bool grc::button::render() const
{
    if (grc::view::render())
    {
        if (this->buttonKeyDown)
        {
            this->drawRect(this->frame, this->focuscolor);
        }
        else
        {
            this->drawRect(this->frame, this->background);
        }
        return true;
    }else {
        return false;
    }
}