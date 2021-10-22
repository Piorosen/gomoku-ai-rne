#include "manager.hpp"
#include <vector>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;
using namespace core;

vector<scorePoint> notFoundAi(color term, vector<vector<color>> board)
{
    return vector<scorePoint>();
}

scorePoint selectNode(vector<scorePoint> item)
{
    int idx = min((int)item.size() - 1, rand() % 3);
    return item[idx];
}

color winCheck(vector<vector<color>> board)
{
    int winCount = 5;

    for (int y = 0; y < board.size(); y++)
    {
        color cur = color::none;
        int count = 0;
        for (int x = 0; x < board[y].size(); x++)
        {
            if (cur != board[y][x])
            {
                cur = board[y][x];
                count = 1;
            }
            else if (cur != color::none)
            {
                count += 1;
                if (count == 3)
                {
                    return cur;
                }
            }
        }
    }

    return color::none;
}

int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL));

    manager::shared->init();

    manager::shared->setNotFoundAi(notFoundAi);
    manager::shared->setWinCheck(winCheck);
    manager::shared->setDefaultAiCalculateTimeOut(500);
    manager::shared->setSelectNode(selectNode);

    manager::shared->run();
}