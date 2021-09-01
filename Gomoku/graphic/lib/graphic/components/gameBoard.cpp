#define GL_SILENCE_DEPRECATION

#include <graphic/components/gameBoard.h>
#include <glut.h>

bool grc::gameBoard::render() const
{
    if (!getHidden())
    {
        this->drawRect(this->frame, this->background);

        propagation();
        return true;
    }
    else
    {
        return false;
    }
}