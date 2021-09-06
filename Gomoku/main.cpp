#include "design/mainViewController.hpp"
#include "design/gameViewController.hpp"
#include "design/treeViewController.hpp"

#include <spdlog/spdlog.h>

#include <filesystem>

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        spdlog::info("{} : \"{}\"", i, argv[i]);
    }

    spdlog::info("{}", std::filesystem::current_path().c_str());
    grc::application::shared->initialize({500, 700}, "오목 : 그것이 알고 싶다.");
    decltype(auto) mainVC = std::make_shared<mainViewController>();
    decltype(auto) gameVC = std::make_shared<gameViewController>();

    gameVC->buttonBack = [&mainVC, &gameVC](unsigned char key)
    {
        spdlog::info("gameVC : button back button");
        if (key == 127)
        {
            grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(mainVC));
        }
        else
        {
            switch (key)
            {
            case '1':
                gameVC->newItem("h8 i9 i6 i10 g9 h10 f10 i7 g11 h11 g12 g10 h12 i13 i12 f12 i8 g8 e10 e9 h13 f11 j11 k10 j10");
                break;

            case '2':
                gameVC->newItem("h8,i9,i6 i10 h7,g9 g9,h10 f10 i7 g11 h11 g12 g10 h12 i13 i12 f12 i8 g8 e10 e9 h13 f11 j11 k10 j10");
                break;
            case '3':
                gameVC->clear();
                break;

            default:
                break;
            }
        }
    };

    mainVC->buttonAiMatch = []()
    { spdlog::info("mainVC : button ai match"); };

    mainVC->buttonContinueGame = []()
    { spdlog::info("mainVC : button continue game"); };

    mainVC->buttonNewGame = [&gameVC]()
    {
        spdlog::info("mainVC : button new game");
        grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameVC));
    };

    mainVC->buttonTree = []()
    { spdlog::info("mainVC : button tree"); };

    grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(mainVC));
    grc::application::shared->run();
}