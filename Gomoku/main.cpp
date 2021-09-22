#include "manager.hpp"
#include <vector>
#include <functional>

using namespace std;

vector<point> notFoundAi(color term, vector<vector<color>> board)
{
    return vector<point>();
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
    manager::shared->run();

    manager::shared->setNotFoundAi(notFoundAi);
    manager::shared->setWinCheck(winCheck);
}