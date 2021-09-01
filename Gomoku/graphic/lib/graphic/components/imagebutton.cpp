#define GL_SILENCE_DEPRECATION

#include <graphic/components/imagebutton.h>
#include <glut.h>

bool grc::imagebutton::click(int state, int x, int y) { 
    auto r = grc::view::click(state, x, y);

    if (this->buttonKeyDown) {
        if (state == 1) { 
            this->buttonKeyDown = false;
            glutPostRedisplay();
        }
    }else if (!this->buttonKeyDown && r) {
        if (state == 0) {
            this->buttonKeyDown = true;
            glutPostRedisplay();
        }
    }

    return r;
}

void grc::imagebutton::render() const
{
    if (this->buttonKeyDown && this->focusImageId.has_value()) {
        this->drawImage(this->frame, this->focusImageId.value());
    }else if (!this->buttonKeyDown && this->backgroundImageId.has_value()) {
        this->drawImage(this->frame, this->backgroundImageId.value());
    }
}