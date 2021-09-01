#include <graphic/components/imageview.h>
#include <glut.h>
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