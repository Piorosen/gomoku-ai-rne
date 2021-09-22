#include "design/mainViewController.hpp"
#include "design/gameViewController.hpp"
#include "design/treeViewController.hpp"
#include "design/gameviewAIvsAIController.hpp"
#include "design/gameViewHumanvsAIController.hpp"

#include <core/jsonManager.hpp>
#include <spdlog/spdlog.h>

#include <tuple>

#include <string>
#include <filesystem>
#include <algorithm>
#include <random>

enum class color
{
    white,
    black,
    none
};

struct point
{
    int x;
    int y;
    double score = 0;
};

class manager
{
private:
    void initai(bool resetAi = false)
    {
        if (resetAi)
        {
            core::jsonManager manager;
            manager.reLoad("./resources/ai/games.json");
            manager.saveJson("./resources/ai/ai.json");
        }
        else
        {
            core::ai::shared->loadAI("./resources/ai/ai.json");
        }
    }

    void initapplication()
    {
        // spdlog::info("{}", std::filesystem::current_path().u8string());
        grc::application::shared->initialize({500, 700}, "오목 : 그것이 알고 싶다.");
    }

    void initui()
    {
        gameAiVC->buttonBack = [this]()
        {
            grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(this->mainVC));
        };

        gameAiVC->buttonNext = [this](std::vector<grc::point> *list) -> std::optional<grc::point>
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

        gameVC->boardChanged = [this](std::vector<grc::point> *list)
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

        gameVC->buttonBack = [this](unsigned char key)
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
                case 'r':
                    gameVC->clear();
                    break;

                default:
                    break;
                };
            }
        };

        mainVC->buttonAiMatch = [this]()
        {
            spdlog::info("mainVC : button ai match");
            gameAiVC->clear();

            grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameAiVC));
        };

        mainVC->buttonContinueGame = [this]()
        {
            spdlog::info("mainVC : button continue game");
            gameHumanVC->clear();

            grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameHumanVC));
        };

        mainVC->buttonNewGame = []()
        {
            spdlog::info("mainVC : button new game");
        };

        mainVC->buttonTree = [this]()
        {
            spdlog::info("mainVC : button tree");
            gameVC->clear();

            grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameVC));
        };
    }

    std::optional<std::function<color(std::vector<std::vector<color>>)>> winCheck = std::nullopt;
    std::optional<std::function<std::vector<point>(color, std::vector<std::vector<color>>)>> notFoundAi = std::nullopt;

public:
    static std::unique_ptr<manager> shared;

    void setWinCheck(std::function<color(std::vector<std::vector<color>>)> check)
    {
        this->winCheck = check;
    }

    void setNotFoundAi(std::function<std::vector<point>(color, std::vector<std::vector<color>>)> sudoAi)
    {
        this->notFoundAi = sudoAi;
    }

    void init(bool resetAi = false)
    {
        initapplication();

        this->mainVC = std::make_shared<mainViewController>();
        this->gameVC = std::make_shared<gameViewController>();
        this->gameAiVC = std::make_shared<gameviewAIvsAIController>();
        this->gameHumanVC = std::make_shared<gameViewHumanvsAIController>();

        initai(resetAi);
        initui();
    }

    void run()
    {
        grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(mainVC));
        grc::application::shared->run();
    }

protected:
    std::shared_ptr<mainViewController> mainVC;
    std::shared_ptr<gameViewController> gameVC;
    std::shared_ptr<gameviewAIvsAIController> gameAiVC;
    std::shared_ptr<gameViewHumanvsAIController> gameHumanVC;
};

std::unique_ptr<manager> manager::shared = std::make_unique<manager>();
