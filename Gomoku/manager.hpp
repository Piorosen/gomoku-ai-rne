#include "design/mainViewController.hpp"
#include "design/gameViewController.hpp"
#include "design/gameviewAIvsAIController.hpp"
#include "design/gameViewHumanvsAIController.hpp"

#include <core/jsonManager.hpp>
#include <spdlog/spdlog.h>

#include <tuple>

#include <string>
#include <filesystem>
#include <algorithm>
#include <random>
#include <time.h>

class manager
{
private:
    void initai(bool resetAi = false)
    {
        if (resetAi)
        {
            core::jsonManager::reLoad("./resources/ai/games.json");
            core::jsonManager::saveJson("./resources/ai/ai.json");
        }
        else
        {
            core::ai::shared->loadAI("./resources/ai/ai.json");
        }
    }

    void initapplication()
    {
// spdlog::info("{}", std::filesystem::current_path().u8string());
#if defined(_WIN32)
        grc::application::shared->initialize({500, 700}, "Gomoku : I want to know that.");
#else
        grc::application::shared->initialize({500, 700}, "오목 : 그것이 알고 싶다.");
#endif

        grc::application::shared->closedEvent = []()
        {
            spdlog::info("Close Event : AI Save Start");
            core::jsonManager::saveJson("./resources/ai/ai_new.json");
            spdlog::info("Close Event : AI Save End");
            time_t timer = time(NULL);
            struct tm *t = localtime(&timer);
            printf("Now Year: %d\n", t->tm_year + 1900);
            printf("Now Month: %d\n", t->tm_mon + 1);
            printf("Now Day: %d\n", t->tm_mday);
            printf("Now Hour: %d\n", t->tm_hour);
            printf("Now Min: %d\n", t->tm_min);
            printf("Now Sec: %d\n", t->tm_sec);

            spdlog::info("Close Event : File Rename");
            char p[256];
            sprintf(p, "%s_%d%2d%2d%2d%2d%2d", "./resources/ai/ai", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
            rename("./resources/ai/ai.json", p);
            rename("./resources/ai/ai_new.json", "./resources/ai/ai.json");
            spdlog::info("Close Event : Finished");
        };
    }

    void initui()
    {

        gameHumanVC->buttonBack = [this]()
        {
            grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(this->mainVC));
        };

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
                int random = std::random_device{}() % 3;
                int idx = std::min((int)itemList.size() - 1, random);

                pt.push_back(itemList[idx].point);
                auto nextList = core::ai::shared->getNextNode(pt);

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
                spdlog::info("time sort");

                for (int i = 0; i < itemList.size(); i++)
                {
                    gameVC->setPredict({itemList.at(i).point.x, itemList.at(i).point.y}, i + 1);
                }
            }

            spdlog::info("time Check End");

            if (winCheck)
            {
                std::vector<std::vector<core::color>> v;
                for (int y = 0; y < 15; y++)
                {
                    std::vector<core::color> line;
                    for (int x = 0; x < 15; x++)
                    {
                        line.push_back(core::color::none);
                    }
                    v.push_back(line);
                }
                for (int i = 0; i < pt.size(); i++)
                {
                    v[pt[i].y][pt[i].x] = i % 2 == 0 ? core::color::black
                                                     : core::color::white;
                }
                auto result = winCheck(v);
                gameVC->showWinView(result);

                spdlog::info("----- Result : Win Check -----");
                std::string dummy;
                switch (result)
                {
                case core::color::black:
                    spdlog::info("----- [ BLACK ] -----");
                    core::ai::shared->appendAI(pt, result);
                    break;
                case core::color::white:
                    spdlog::info("----- [ WHITE ] -----");
                    core::ai::shared->appendAI(pt, result);
                    break;
                case core::color::none:
                    spdlog::info("----- [ NONE ] -----");
                    break;
                }

                spdlog::info("----- Result : Win Check -----");
            }
            else
            {
                spdlog::critical("not found win Check");
            }
        };

        gameVC->buttonBack = [this](unsigned char key)
        {
            spdlog::info("gameVC : button back button");
            if (key == 27)
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
            gameHumanVC->setAiTern(core::color::black);
            gameHumanVC->clear();
            grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameHumanVC));
        };

        mainVC->buttonNewGame = [this]()
        {
            gameHumanVC->setAiTern(core::color::white);
            gameHumanVC->clear();
            grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameHumanVC));
        };

        mainVC->buttonTree = [this]()
        {
            spdlog::info("mainVC : button tree");
            gameVC->clear();

            grc::application::shared->setViewController(std::static_pointer_cast<grc::viewcontroller>(gameVC));
        };
    }

    std::function<core::color(std::vector<std::vector<core::color>>)> winCheck;

public:
    static std::unique_ptr<manager> shared;

    // default : 500ms
    void setDefaultAiCalculateTimeOut(int milliseconds)
    {
        core::ai::shared->setDefaultAiCalculateTimeOut(milliseconds);
    }

    void setWinCheck(core::color (*check)(std::vector<std::vector<core::color>>))
    {
        gameAiVC->setWinCheck(check);
        gameHumanVC->setWinCheck(check);
        this->winCheck = check;
    }

    void setWinCheck(std::function<core::color(std::vector<std::vector<core::color>>)> check)
    {
        gameAiVC->setWinCheck(check);
        gameHumanVC->setWinCheck(check);
        this->winCheck = check;
    }

    void setNotFoundAi(std::vector<core::scorePoint> (*sudoAi)(core::color, std::vector<std::vector<core::color>>))
    {
        core::ai::shared->setNotFoundAi(sudoAi);
    }
    void setNotFoundAi(std::function<std::vector<core::scorePoint>(core::color, std::vector<std::vector<core::color>>)> sudoAi)
    {
        core::ai::shared->setNotFoundAi(sudoAi);
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

    void showPredictNumer(bool show)
    {
    }
    void showAllNumber(bool show)
    {
    }

protected:
    std::shared_ptr<mainViewController> mainVC;
    std::shared_ptr<gameViewController> gameVC;
    std::shared_ptr<gameviewAIvsAIController> gameAiVC;
    std::shared_ptr<gameViewHumanvsAIController> gameHumanVC;
};

std::unique_ptr<manager> manager::shared = std::make_unique<manager>();
