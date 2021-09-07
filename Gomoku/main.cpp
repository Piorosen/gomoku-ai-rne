#include "design/mainViewController.hpp"
#include "design/gameViewController.hpp"
#include "design/treeViewController.hpp"

#include <core/jsonManager.hpp>

#include <spdlog/spdlog.h>

#include <filesystem>

int main(int argc, char **argv)
{
    // core::ai::shared->loadAI("/Users/aoikazto/Downloads/ai.json");
    core::jsonManager manager;
    manager.reLoad("/Users/aoikazto/Downloads/games.json");
    manager.saveJson("/Users/aoikazto/Downloads/ai.json");

    for (int i = 0; i < argc; i++)
    {
        spdlog::info("{} : \"{}\"", i, argv[i]);
    }

    spdlog::info("{}", std::filesystem::current_path().c_str());
    grc::application::shared->initialize({500, 700}, "오목 : 그것이 알고 싶다.");
    decltype(auto) mainVC = std::make_shared<mainViewController>();
    decltype(auto) gameVC = std::make_shared<gameViewController>();

    gameVC->boardChanged = [&gameVC](std::vector<grc::point> *list)
    {
        core::sqeuence pt;
        for (auto &item : *list)
        {
            pt.push_back({item.x, item.y});
        }

        auto itemList = core::ai::shared->getNextNode(pt);
        gameVC->clear(1);
        for (auto &item : itemList)
        {
            gameVC->setPredict({item.point.x, item.point.y});
        }
    };

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
            case '3':
                gameVC->clear();
                break;

            default:
                break;
            };
        }
    };

    mainVC->buttonAiMatch = []()
    { spdlog::info("mainVC : button ai match"); };

    mainVC->buttonContinueGame = []()
    { spdlog::info("mainVC : button continue game"); };

    mainVC->buttonNewGame = [&gameVC]()
    {
        spdlog::info("mainVC : button new game");
        gameVC->clear();

        grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameVC));
    };

    mainVC->buttonTree = []()
    { spdlog::info("mainVC : button tree"); };

    grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(mainVC));
    grc::application::shared->run();
}