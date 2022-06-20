#include "manager.hpp"
#include <vector>
#include <functional>
#include <stdlib.h>

using namespace std;
using namespace core;
int check1(vector<vector<color>> arr) {
    int temp1 = 0; int temp2 = 0;
    //가로 체크
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (arr[i][j] == color::black) {
                temp1++;
                if (temp1 == 5) {
                    temp2 = 0;
                    return 1;
                }
            }
            else if (arr[i][j] == color::white) {
                temp2++;
                if (temp2 == 5) {
                    temp1 = 0;
                    return 2;
                }
            }
            else if (arr[i][j] == color::none) {
                temp1 = 0, temp2 = 0;
            }
        }
        temp1 = 0, temp2 = 0;
    }
    return 0;
}
 
int check2(vector<vector<color>> arr) {
    int temp1 = 0; int temp2 = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (arr[j][i] == color::black) {
                temp1++;
                if (temp1 == 5) {
                    temp2 = 0;
                    return 1;
                }
            }
            else if (arr[j][i] == color::white) {
                temp2++;
                if (temp2 == 5) {
                    temp1 = 0;
                    return 2;
                }
            }
            else if (arr[i][j] == color::none) {
                temp1 = 0, temp2 = 0;
            }
        }
        temp1 = 0, temp2 = 0;
    }
    return 0;
}
 
int check3(vector<vector<color>> arr) {
    for (int i = 2; i < 14; i++)
    {
        for (int j = 2; j < 14; j++)
        {
            if (arr[j - 2][i - 2] == color::black && arr[j - 1][i - 1] == color::black && arr[j][i] == color::black && arr[j + 1][i + 1] == color::black && arr[j + 2][i + 2] == color::black) {
                return 1;
            }
            else if (arr[j - 2][i - 2] == color::white && arr[j - 1][i - 1] == color::white && arr[j][i] == color::white && arr[j + 1][i + 1] == color::white && arr[j + 2][i + 2] == color::white) {
                return 2;
            }
            if (arr[j + 2][i - 2] == color::black && arr[j + 1][i - 1] == color::black && arr[j][i] == color::black && arr[j - 1][i + 1] == color::black && arr[j - 2][i + 2] == color::black) {
                return 1;
            }
            else if (arr[j + 2][i - 2] == color::white && arr[j + 1][i - 1] == color::white && arr[j][i] == color::white && arr[j - 1][i + 1] == color::white && arr[j - 2][i + 2] == color::white) {
                return 2;
            }
        }
    }
    return 0;
}

vector<scorePoint> notFoundAi(color term, vector<vector<color>> board)
{
    return vector<scorePoint>();
}

color winCheck(vector<vector<color>> board)
{
    int winCount = 5;

    // check : vertical
    // check : horizontal
    // check : cross
    int a = check1(board);
    int b = check2(board);
    int c = check3(board);

    if (a == 1 || b == 1 || c == 1) {
        return color::black;
    }
    else if (a == 2 || b == 2 || c == 2) {
        return color::white;
    }
    else if (a == 0 || b == 0 || c == 0) {
        return color::none;
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