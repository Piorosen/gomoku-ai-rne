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

    // check : vertical
    // check : horizontal
    // check : cross

    return color::none;
}

int main(int argc, char **argv)
{
    manager::shared->init();

    manager::shared->setNotFoundAi(notFoundAi);
    manager::shared->setWinCheck(winCheck);
    manager::shared->setDefaultAiCalculateTimeOut(500);

    manager::shared->run();
}