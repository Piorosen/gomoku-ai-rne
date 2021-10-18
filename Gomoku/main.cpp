#include "manager.hpp"
#include <vector>
#include <functional>
#include <stdlib.h>

using namespace std;
using namespace core;

vector<scorePoint> notFoundAi(color term, vector<vector<color>> board)
{
    return vector<scorePoint>();
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
    manager::shared->init();

    manager::shared->setNotFoundAi(notFoundAi);
    manager::shared->setWinCheck(winCheck);
    manager::shared->setDefaultAiCalculateTimeOut(500);
    // manager::shared->showPredictNumer(false);
    // manager::shaerd->showAllNumber(true);

    /**
 * TODO : 
 * 1. 인공지능 모델 재 학습 기능 구현하기
 * 2. 숫자 지우기 모드
 * 3. 
 * 
 */

    manager::shared->run();
}