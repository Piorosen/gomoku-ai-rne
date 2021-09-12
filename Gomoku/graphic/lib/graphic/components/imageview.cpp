#include <graphic/components/imageview.h>
#if defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <graphic/application.h>

bool grc::imageview::render() const
{
    if (!getHidden())
    {
        if (this->imageId.has_value())
        {
            this->drawImage(this->frame, this->imageId.value());
        }

        propagation();
        return true;
    }
    else
    {
        return false;
    }
}