#define GL_SILENCE_DEPRECATION

#include <graphic/components/popupview.h>
#if defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

bool grc::popupview::render() const
{
    if (!getHidden())
    {
        glBegin(GL_TRIANGLES);
        // glVertex2f();

        glEnd();
        propagation();
        return true;
    }
    else
    {
        return false;
    }
}