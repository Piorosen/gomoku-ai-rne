#include "design/mainViewController.h"

#include <memory>
#include <spdlog/spdlog.h>
#include <glut.h>

#include <filesystem>

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++) {
        spdlog::info("{} : \"{}\"", i, argv[i]);
    }

    spdlog::info("{}", std::filesystem::current_path().c_str());
    grc::application::shared->initialize({500, 700}, "오목 : 그것이 알고 싶다.");
    auto p = makeViewController();
    grc::application::shared->setViewController(std::move(p));
    grc::application::shared->run();   
}