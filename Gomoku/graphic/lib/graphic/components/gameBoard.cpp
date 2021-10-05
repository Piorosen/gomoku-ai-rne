#define GL_SILENCE_DEPRECATION

#include <graphic/components/gameBoard.h>
#if defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <string>
#include <spdlog/spdlog.h>

void grc::gameBoard::setAutoColorChange(bool value, int color)
{
    autoColorChange = value;
    this->color = color;
}

bool grc::gameBoard::getPredictNumber() const
{
    return predictNum;
}

bool grc::gameBoard::getAllNumber() const
{
    return allNum;
}

void grc::gameBoard::setPredictNumber(bool show)
{
    predictNum = show;
    glutPostRedisplay();
}

void grc::gameBoard::setAllNumber(bool show)
{
    allNum = show;
    glutPostRedisplay();
}

void grc::gameBoard::setClickDisable(bool value)
{
    clickDisable = value;
}
bool grc::gameBoard::getClickDisable() const
{
    return clickDisable;
}

int grc::gameBoard::click(int state, int x, int y)
{
    auto p = grc::view::click(state, x, y);

    if (p != 2)
    {
        return p;
    }

    // keydown
    if (state == 0 && !clickDisable)
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
            if (this->setState(convPt, this->color + 1))
            {
                if (autoColorChange)
                {
                    this->color = !this->color;
                }
            }
        }
    }

    return p;
}

std::vector<grc::point> grc::gameBoard::getSequence()
{
    return this->point;
}

bool grc::gameBoard::setState(grc::point pos, int state)
{
    int value = boardState[pos.y][pos.x] % 100000;
    if (value == 1 || value == 2)
    {
        spdlog::warn("Board Info : setState(error point) : [{}, {}]", pos.x, pos.y);
        return false;
    }

    counting++;
    boardState[pos.y][pos.x] = state + (counting * 100000);
    point.push_back(pos);
    if (boardChanged)
    {
        boardChanged(&this->point);
        glutPostRedisplay();
    }
    return true;
}

bool grc::gameBoard::setPredict(grc::point pos, int state, int text)
{
    if (boardState[pos.y][pos.x])
    {
        spdlog::warn("Board Info : setState(error point) : [{}, {}, {}]", boardState[pos.y][pos.x], pos.x, pos.y);
        // return false;
    }

    boardState[pos.y][pos.x] = state + (text * 100000);
    glutPostRedisplay();
    return true;
}

void grc::gameBoard::clear(int mode)
{
    spdlog::info("Board info : Clear [{}]", mode);

    if (mode == 0)
    {
        this->mode = 0;
        this->color = 0;
        point.clear();
        counting = 0;
        for (int y = 0; y < boardSize.height; y++)
        {
            for (int x = 0; x < boardSize.width; x++)
            {
                boardState[y][x] = 0;
            }
        }
        if (boardChanged)
        {
            boardChanged(&this->point);
        }
    }
    else
    {
        for (int y = 0; y < boardSize.height; y++)
        {
            for (int x = 0; x < boardSize.width; x++)
            {
                if (boardState[y][x] % 100000 == 3)
                {
                    boardState[y][x] = 0;
                }
            }
        }
    }

    glutPostRedisplay();
}

bool grc::gameBoard::render() const
{
    if (!getHidden())
    {
        spdlog::info("rendering game board");

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
                    if (boardState[y][x] > 100000 && this->allNum)
                    {
                        this->drawBitmapText(std::to_string(boardState[y][x] / 100000), pos);
                    }

                    break;

                case 2:
                    this->drawCircle(pos, 15, whiteColor);
                    if (boardState[y][x] > 100000 && this->allNum)
                    {
                        this->drawBitmapText(std::to_string(boardState[y][x] / 100000), pos);
                    }
                    break;

                case 3:
                    this->drawCircle(pos, 15, predictColor);
                    if (boardState[y][x] > 100000 && this->predictNum)
                    {
                        this->drawBitmapText(std::to_string(boardState[y][x] / 100000), pos);
                    }
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