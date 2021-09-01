#define GL_SILENCE_DEPRECATION

#define MATH_PI 3.14159265359

#include <graphic/application.h>
#include <graphic/components/view.h>
#include <GLUT/glut.h>
#include <spdlog/spdlog.h>

bool grc::view::click(int state, int x, int y) {
    for (auto &p : this->controls)
    {
        p->click(state, x, y);
    }

    if (this->frame.location.x < x && x < this->frame.location.x + this->frame.size.width &&
        this->frame.location.y < y && y < this->frame.location.y + this->frame.size.height)
    {
        spdlog::info("[{}, {}, {}]", state, x, y);
        return true;
    }else {
        return false;
    }
}

void grc::view::render() const
{
    spdlog::info("View Rendering");
    this->drawRect(this->frame, this->background);
}

void grc::view::drawRect(grc::rect size, grc::color color) const
{
    glColor4f(color.red / 255.0, color.green / 255.0, color.blue / 255.0, color.alpha / 255.0);
    glBegin(GL_QUADS); //4점이 하나의 사각형을 구성한다. 반시계 방향으로 4점의 vertex를 지정해줘야 한다.
    grc::point lup = {size.location.x, size.location.y + size.size.height};
    grc::point rup = {size.location.x + size.size.width, size.location.y + size.size.height};
    grc::point lbp = {size.location.x, size.location.y};
    grc::point rbp = {size.location.x + size.size.width, size.location.y};

    const auto &displaySize = grc::application::shared->getSize();
    float displayX = displaySize.width / 2,
          displayY = -displaySize.height / 2;

    glVertex2f(lbp.x / displayX - 1, lbp.y / displayY + 1); // x, y
    glVertex2f(rbp.x / displayX - 1, rbp.y / displayY + 1);
    glVertex2f(rup.x / displayX - 1, rup.y / displayY + 1);
    glVertex2f(lup.x / displayX - 1, lup.y / displayY + 1);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); //흰색 지정
}

void grc::view::drawCircle(grc::point pt, float radius, grc::color color) const
{
    const int lineAmount = (int)radius; //# of triangles used to draw circle

    double twicePi = 2.0f * MATH_PI;
    const auto &displaySize = grc::application::shared->getSize();
    float displayX = displaySize.width / 2,
          displayY = -displaySize.height / 2;

    float ptX = pt.x / displayX - 1, ptY = pt.y / displayY + 1;
    float szX = (radius * 2) / displaySize.width, szY = (radius * 2) / displaySize.height;

    glColor4f(color.red / 255.0, color.green / 255.0, color.blue / 255.0, color.alpha / 255.0);
    glBegin(GL_POLYGON);

    for (int i = 0; i <= lineAmount; i++)
    {
        auto xx = ptX + (szX * cos(i * twicePi / lineAmount));
        auto yy = ptY + (szY * sin(i * twicePi / lineAmount));
        glVertex2f(xx, yy);
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); //흰색 지정
}

void grc::view::drawLine(grc::point x, grc::point y, float thin, grc::color color) const
{
    const auto &displaySize = grc::application::shared->getSize();
    float displayX = displaySize.width / 2,
          displayY = -displaySize.height / 2;

    glLineWidth(thin);
    glColor4f(color.red / 255.0, color.green / 255.0, color.blue / 255.0, color.alpha / 255.0);
    glBegin(GL_LINES);
    glVertex2f(x.x / displayX - 1, x.y / displayY + 1);
    glVertex2f(y.x / displayX - 1, y.y / displayY + 1);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); //흰색 지정
}

void grc::view::drawImage(grc::rect size, unsigned int imageId) const
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

    glBindTexture(GL_TEXTURE_2D, imageId);
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