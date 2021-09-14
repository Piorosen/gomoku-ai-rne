#include "design/mainViewController.hpp"
#include "design/gameViewController.hpp"
#include "design/treeViewController.hpp"
#include "design/gameviewAIvsAIController.hpp"

#include <core/jsonManager.hpp>
#include <spdlog/spdlog.h>

#include <string>
#include <filesystem>
#include <algorithm>
#include <random>

int main(int argc, char **argv)
{
    core::ai::shared->loadAI("./resources/ai/ai.json");
    // core::jsonManager manager;
    // manager.reLoad("./resources/ai/games.json");
    // manager.saveJson("./resources/ai/ai.json");
    for (int i = 0; i < argc; i++)
    {
        spdlog::info("{} : \"{}\"", i, argv[i]);
    }

    spdlog::info("{}", std::filesystem::current_path().u8string());
    grc::application::shared->initialize({500, 700}, "오목 : 그것이 알고 싶다.");
    decltype(auto) mainVC = std::make_shared<mainViewController>();
    decltype(auto) gameVC = std::make_shared<gameViewController>();
    decltype(auto) gameAiVC = std::make_shared<gameviewAIvsAIController>();

    gameAiVC->buttonBack = [&mainVC]()
    {
        grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(mainVC));
    };

    gameAiVC->buttonNext = [&gameAiVC](std::vector<grc::point> *list) -> std::optional<grc::point>
    {
        core::sqeuence pt;
        for (auto &item : *list)
        {
            pt.push_back({item.x, item.y});
        }
        auto itemList = core::ai::shared->getNextNode(pt);

        if (itemList.size() == 0)
        {
            spdlog::critical("not found next Step");
            return std::nullopt;
        }
        else
        {
            std::sort(itemList.begin(), itemList.end(), [](core::scorePoint &a, core::scorePoint &b)
                      { return a.score - b.score; });
            int random = std::random_device{}() % 3;
            int idx = std::min((int)itemList.size() - 1, random);

            pt.push_back(itemList[idx].point);
            auto nextList = core::ai::shared->getNextNode(pt);

            std::sort(nextList.begin(), nextList.end(), [](core::scorePoint &a, core::scorePoint &b)
                      { return a.score - b.score; });

            for (int i = 0; i < nextList.size(); i++)
            {
                gameAiVC->setPredict({nextList[i].point.x, nextList[i].point.y}, i + 1);
            }
            return grc::point{itemList[idx].point.x, itemList[idx].point.y};
        }
    };

    gameVC->boardChanged = [&gameVC](std::vector<grc::point> *list)
    {
        spdlog::info("time Check Start");
        spdlog::info("update board changed");
        core::sqeuence pt;
        for (auto &item : *list)
        {
            pt.push_back({item.x, item.y});
        }
        spdlog::info("time list to sequence");
        gameVC->clear(1);
        spdlog::info("time gameVC Clear 1");

        auto itemList = core::ai::shared->getNextNode(pt);

        spdlog::info("time get Next Node");
        if (itemList.size() != 0)
        {
            std::sort(itemList.begin(), itemList.end(), [](core::scorePoint &a, core::scorePoint &b)
                      { return a.score - b.score; });
            spdlog::info("time sort");

            for (int i = 0; i < itemList.size(); i++)
            {
                gameVC->setPredict({itemList.at(i).point.x, itemList.at(i).point.y}, i + 1);
            }
        }

        spdlog::info("time Check End");
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

    mainVC->buttonAiMatch = [&gameAiVC]()
    {
        spdlog::info("mainVC : button ai match");
        gameAiVC->clear();

        grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameAiVC));
    };

    mainVC->buttonContinueGame = []()
    {
        spdlog::info("mainVC : button continue game");
    };

    mainVC->buttonNewGame = []()
    {
        spdlog::info("mainVC : button new game");
    };

    mainVC->buttonTree = [&gameVC]()
    {
        spdlog::info("mainVC : button tree");
        gameVC->clear();

        grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameVC));
    };

    grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(mainVC));
    grc::application::shared->run();
}