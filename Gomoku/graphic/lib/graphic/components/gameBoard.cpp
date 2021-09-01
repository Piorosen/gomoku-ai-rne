#define GL_SILENCE_DEPRECATION

#include <graphic/components/gameBoard.h>
#include <glut.h>

// int click(int state, int x, int y)
// {
//     return grc::view::click(state, x, y);
// }

void grc::gameBoard::setState(grc::point pos, int state)
{
    boardState[pos.y][pos.x] = state;
    glutPostRedisplay();
}

bool grc::gameBoard::render() const
{
    if (!getHidden())
    {
        this->drawRect(this->frame, this->background);

        float w = (float)this->frame.size.width / (this->boardSize.width + 1);
        float h = (float)this->frame.size.height / (this->boardSize.height + 1);

        for (int x = 0; x < this->boardSize.width; x++)
        {
            grc::point start = {this->frame.location.x + (int)((x + 1) * w), this->frame.location.y};
            grc::point end = {this->frame.location.x + (int)((x + 1) * w), this->frame.location.y + this->frame.size.height};

            this->drawLine(start, end, 3, this->lineColor);
        }

        for (int y = 0; y < this->boardSize.height; y++)
        {
            grc::point start = {this->frame.location.x, this->frame.location.y + (int)((y + 1) * h)};
            grc::point end = {this->frame.location.x + this->frame.size.width, this->frame.location.y + (int)((y + 1) * h)};

            this->drawLine(start, end, 3, this->lineColor);
        }

        for (int y = 0; y < boardState.size(); y++)
        {
            for (int x = 0; x < boardState[y].size(); x++)
            {
                grc::point pos = {this->frame.location.x + (int)((x + 1) * w),
                                  this->frame.location.y + (int)((y + 1) * h)};

                switch (boardState[y][x])
                {
                case 1:
                    this->drawCircle(pos, 15, blackColor);
                    break;

                case 2:
                    this->drawCircle(pos, 15, whiteColor);
                    break;

                case 3:
                    this->drawCircle(pos, 15, predictColor);
                    break;

                default:
                    break;
                }
            }
        }
        propagation();
        return true;
    }
    else
    {
        return false;
    }
}