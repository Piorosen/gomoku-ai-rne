#define GL_SILENCE_DEPRECATION

#include <graphic/components/button.h>
#include <GL/glut.h>

int grc::button::click(int state, int x, int y)
{
    auto r = grc::view::click(state, x, y);
    if (r != 2)
    {
        return r;
    }

    if (this->buttonKeyDown)
    {
        if (state == 1)
        {
            if (buttonDown)
            {
                buttonDown();
            }
            this->buttonKeyDown = false;
            glutPostRedisplay();
        }
    }
    else if (!this->buttonKeyDown)
    {
        if (state == 0)
        {
            this->buttonKeyDown = true;
            glutPostRedisplay();
        }
    }

    return r;
}

bool grc::button::render() const
{
    if (!getHidden())
    {
        if (this->buttonKeyDown)
        {
            this->drawRect(this->frame, this->focuscolor);
        }
        else
        {
            this->drawRect(this->frame, this->background);
        }

        propagation();
        return true;
    }
    else
    {
        return false;
    }
}