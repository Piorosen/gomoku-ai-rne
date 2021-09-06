#define GL_SILENCE_DEPRECATION

#include <graphic/components/gameBoard.h>
#include <GLUT/glut.h>
#include <string>
#include <spdlog/spdlog.h>

int grc::gameBoard::click(int state, int x, int y)
{
    auto p = grc::view::click(state, x, y);

    // keydown
    if (state == 0)
    {
        float ptX = x - this->frame.location.x;
        float ptY = y - this->frame.location.y;

        float sizeX = this->frame.size.width / (float)(this->boardSize.width + 1);
        float sizeY = this->frame.size.height / (float)(this->boardSize.height + 1);

        ptX += sizeX / 2;
        ptY += sizeY / 2;

        grc::point pt = {(int)(ptX / sizeX), (int)(ptY / sizeY)};
        grc::point convPt = {std::min(std::max(0, pt.x - 1), this->boardSize.width - 1),
                             std::min(std::max(0, pt.y - 1), this->boardSize.height - 1)};

        spdlog::info("Board info : Click [{}, {}]", pt.x, pt.y);

        if (mode == 0)
        {
            this->setState(convPt, this->color + 1);
            this->color = !this->color;
        }
    }

    return p;
}

void grc::gameBoard::setState(grc::point pos, int state)
{
    if (boardState[pos.y][pos.x] > 0)
    {
        spdlog::warn("Board Info : setState(error point) : [{}, {}]", pos.x, pos.y);
        return;
    }

    counting++;
    boardState[pos.y][pos.x] = state + (counting * 100000);
    glutPostRedisplay();
}

void grc::gameBoard::clear()
{
    for (int y = 0; y < boardSize.height; y++)
    {
        for (int x = 0; x < boardSize.width; x++)
        {
            boardState[y][x] = 0;
        }
    }
    counting = 0;
    spdlog::info("Board info : Clear");
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
            grc::point start = {this->frame.location.x + (int)((x + 1) * w), this->frame.location.y + (int)h};
            grc::point end = {this->frame.location.x + (int)((x + 1) * w), this->frame.location.y + this->frame.size.height - (int)h};

            this->drawLine(start, end, 3, this->lineColor);
        }

        for (int y = 0; y < this->boardSize.height; y++)
        {
            grc::point start = {this->frame.location.x + (int)w, this->frame.location.y + (int)((y + 1) * h)};
            grc::point end = {this->frame.location.x + this->frame.size.width - (int)w, this->frame.location.y + (int)((y + 1) * h)};

            this->drawLine(start, end, 3, this->lineColor);
        }

        for (int y = 0; y < boardState.size(); y++)
        {
            for (int x = 0; x < boardState[y].size(); x++)
            {
                grc::point pos = {this->frame.location.x + (int)((x + 1) * w),
                                  this->frame.location.y + (int)((y + 1) * h)};

                switch (boardState[y][x] % 100000)
                {
                case 1:
                    this->drawCircle(pos, 15, blackColor);
                    this->drawBitmapText(std::to_string(boardState[y][x] / 100000), pos);
                    break;

                case 2:
                    this->drawCircle(pos, 15, whiteColor);
                    this->drawBitmapText(std::to_string(boardState[y][x] / 100000), pos);
                    break;

                case 3:
                    this->drawCircle(pos, 15, predictColor);
                    this->drawBitmapText(std::to_string(boardState[y][x] / 100000), pos);
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