#include <graphic/components/imageview.h>
#include <glut.h>
#include <graphic/application.h>

void grc::imageview::render() const
{
    if (this->imageId.has_value())
    {
        grc::point lup = {this->frame.location.x, this->frame.location.y + this->frame.size.height};
        grc::point rup = {this->frame.location.x + this->frame.size.width, this->frame.location.y + this->frame.size.height};
        grc::point lbp = {this->frame.location.x, this->frame.location.y};
        grc::point rbp = {this->frame.location.x + this->frame.size.width, this->frame.location.y};

        const auto &displaySize = grc::application::shared->getSize();
        float displayX = displaySize.width / 2,
              displayY = -displaySize.height / 2;

        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glBindTexture(GL_TEXTURE_2D, this->imageId.value());
        glBegin(GL_QUADS);

        glTexCoord2f(1.0, 1.0);
        glVertex2f(rup.x / displayX - 1, rup.y / displayY + 1);

        glTexCoord2f(0.0, 1.0);
        glVertex2f(lup.x / displayX - 1, lup.y / displayY + 1);

        glTexCoord2f(0.0, 0.0);
        glVertex2f(lbp.x / displayX - 1, lbp.y / displayY + 1); // x, y

        glTexCoord2f(1.0, 0.0);
        glVertex2f(rbp.x / displayX - 1, rbp.y / displayY + 1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
}