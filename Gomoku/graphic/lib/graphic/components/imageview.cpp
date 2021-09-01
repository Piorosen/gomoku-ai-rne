#include <graphic/components/imageview.h>
#include <glut.h>
#include <graphic/application.h>

void grc::imageview::render() const
{
    if (this->imageId.has_value())
    {
        this->drawImage(this->frame, this->imageId.value());
    }
}