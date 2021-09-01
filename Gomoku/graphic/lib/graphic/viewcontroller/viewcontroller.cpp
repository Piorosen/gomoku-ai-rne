#include <graphic/viewcontroller/viewcontroller.h>

void grc::viewcontroller::mouseEvent(int button, int state, int x, int y)
{
    for (auto &v : view)
    {
        v->click(state, x, y);
    }
}

void grc::viewcontroller::render() const
{
    for (auto &v : view)
    {
        v->render();
    }
}