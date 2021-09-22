#include "manager.hpp"

int main(int argc, char **argv)
{
    manager::shared->init();
    manager::shared->run();
}