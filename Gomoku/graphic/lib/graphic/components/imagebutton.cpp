#define GL_SILENCE_DEPRECATION

#include <graphic/components/imagebutton.h>
#include <glut.h>

int grc::imagebutton::click(int state, int x, int y)
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

bool grc::imagebutton::render() const
{
    if (!getHidden())
    {
        if (this->buttonKeyDown && this->focusImageId.has_value())
        {
            this->drawImage(this->frame, this->focusImageId.value());
        }
        else if (!this->buttonKeyDown && this->backgroundImageId.has_value())
        {
            this->drawImage(this->frame, this->backgroundImageId.value());
        }

        propagation();
        return true;
    }
    else
    {
        return false;
    }
}