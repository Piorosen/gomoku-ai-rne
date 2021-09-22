#include <graphic/viewcontroller/viewcontroller.h>

void grc::viewcontroller::mouseEvent(int button, int state, int x, int y)
{
    if (button == 0)
    {
        for (auto &v : view)
        {
            v->click(state, x, y);
        }
    }
    else if (button == 2)
    {
        for (auto &v : view)
        {
            v->rightClick(state, x, y);
        }
    }
}

void grc::viewcontroller::keyboardEvent(unsigned char key, int x, int y)
{
}

void grc::viewcontroller::render() const
{
    for (auto &v : view)
    {
        v->render();
    }
}