#define GL_SILENCE_DEPRECATION

#include <graphic/application.h>
#include <graphic/components/view.h>
#include <GLUT/glut.h>
#include <spdlog/spdlog.h>

void grc::view::render() const
{
    spdlog::info("VIEW");
    glColor4f(background.red / 255.0, background.green / 255.0, background.blue / 255.0, background.alpha / 255.0);
    glBegin(GL_QUADS); //4점이 하나의 사각형을 구성한다. 반시계 방향으로 4점의 vertex를 지정해줘야 한다.
    grc::point lup = {this->frame.location.x, this->frame.location.y + this->frame.size.height};
    grc::point rup = {this->frame.location.x + this->frame.size.width, this->frame.location.y + this->frame.size.height};
    grc::point lbp = {this->frame.location.x, this->frame.location.y};
    grc::point rbp = {this->frame.location.x + this->frame.size.width, this->frame.location.y};

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