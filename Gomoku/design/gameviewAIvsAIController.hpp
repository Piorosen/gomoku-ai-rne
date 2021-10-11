#pragma once
#include <graphic/application.h>
#include <graphic/components/imageview.h>
#include <graphic/utils/imagecollect.h>
#include <graphic/components/imagebutton.h>
#include <graphic/components/gameBoard.h>

#include <core/jsonManager.hpp>

#include <iostream>

#include <cstdlib>
#include <ctime>
#include <functional>
#include <sstream>
#include <optional>

class gameviewAIvsAIController : public grc::viewcontroller
{
private:
    std::shared_ptr<grc::gameBoard> board;
    std::shared_ptr<grc::imageview> winView;

    std::shared_ptr<grc::view> makeVictoryView()
    {
        auto okIdx = grc::imagecollect::shared->add("./resources/ok.png");
        auto ok_focusIdx = grc::imagecollect::shared->add("./resources/ok_focus.png");
        auto black_victoryIdx = grc::imagecollect::shared->add("./resources/black_victory.png");
        auto white_victoryIdx = grc::imagecollect::shared->add("./resources/white_victory.png");

        grc::rect f1;
        f1.location = {100, 175};
        f1.size = {300, 350};
        std::shared_ptr<grc::view> container = std::make_shared<grc::view>(f1, grc::color(0xffffffff));
        // container->setHidden(true);
        // container->setBorder(3, grc::color(0x000000ff));

        grc::rect f2;
        f2.location = {125, 200};
        f2.size = {250, 250};
        winView = std::make_shared<grc::imageview>(f2);
        winView->imageId = black_victoryIdx;

        grc::rect f3;
        f3.location = {175, 450};
        f3.size = {150, 50};
        auto okButton = std::make_shared<grc::imagebutton>(f3);
        okButton->backgroundImageId = okIdx;
        okButton->focusImageId = ok_focusIdx;

        container->controls.push_back(std::static_pointer_cast<grc::view>(winView));
        container->controls.push_back(std::static_pointer_cast<grc::view>(okButton));

        return container;
    }

    void setDesign()
    {
        auto titleIdx = grc::imagecollect::shared->add("./resources/title.png");
        auto backIdx = grc::imagecollect::shared->add("./resources/back.png");
        auto back_focusIdx = grc::imagecollect::shared->add("./resources/back_focus.png");

        grc::rect f1;
        f1.location = {0, 200};
        f1.size = {500, 500};
        grc::size s1 = {15, 15};
        board = std::make_shared<grc::gameBoard>(f1, s1);
        board->setClickDisable(true);

        grc::rect f2;
        f2.location = {0, 0};
        f2.size = {500, 200};
        auto p = std::make_shared<grc::imageview>(f2);
        p->imageId = titleIdx;

        grc::rect f3;
        f3.location = {40, 70};
        f3.size = {60, 60};
        auto p2 = std::make_shared<grc::imagebutton>(f3);
        p2->backgroundImageId = backIdx;
        p2->focusImageId = back_focusIdx;
        p2->buttonDown = [this]()
        {
            if (this->buttonBack)
            {
                this->buttonBack();
            }
        };

        auto menu = this->makeVictoryView();

        view.push_back(std::static_pointer_cast<grc::view>(board));
        view.push_back(std::static_pointer_cast<grc::view>(p));
        view.push_back(std::static_pointer_cast<grc::view>(p2));
        view.push_back(menu);
    }

    std::function<core::color(std::vector<std::vector<core::color>>)> winCheck;

public:
    std::function<void()> buttonBack;
    std::function<std::optional<grc::point>(std::vector<grc::point> *list)> buttonNext;

    void setWinCheck(core::color (*check)(std::vector<std::vector<core::color>>))
    {
        this->winCheck = check;
    }

    void setWinCheck(std::function<core::color(std::vector<std::vector<core::color>>)> check)
    {
        this->winCheck = check;
    }

    virtual void keyboardEvent(unsigned char key, int x, int y) override
    {
        switch (key)
        {
        case 27:
            if (buttonBack)
            {
                buttonBack();
            }
            break;

        case 'r':
        {
            this->clear();
        }
        break;

        case 'a':
        {
            board->setAllNumber(!board->getAllNumber());
        }
        break;
        case 's':
        {
            board->setPredictNumber(!board->getPredictNumber());
        }
        break;

        case 'q':
        {
            auto b = board->getSequence();
            if (b.size() > 0)
            {
                b.pop_back();
            }
            this->clear(0, 0);

            core::sqeuence pt;
            for (auto &item : b)
            {
                pt.push_back({item.x, item.y});
            }
            auto itemList = core::ai::shared->getNextNode(pt);

            for (int i = 0; i < itemList.size(); i++)
            {
                setPredict({itemList[i].point.x, itemList[i].point.y}, i + 1);
            }

            for (int i = 0; i < b.size(); i++)
            {
                board->setState(b[i], (i % 2) + 1);
            }
        }
        break;

        case 'e':
        {
            auto c = board->getSequence();
            if (buttonNext)
            {
                this->clear(0, 0);
                auto p = buttonNext(&c);
                if (p.has_value())
                {
                    c.push_back(p.value());
                }

                for (int i = 0; i < c.size(); i++)
                {
                    board->setState(c[i], (i % 2) + 1);
                }

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
                    for (int i = 0; i < c.size(); i++)
                    {
                        v[c[i].y][c[i].x] = i % 2 == 0 ? core::color::black
                                                       : core::color::white;
                    }
                    auto result = winCheck(v);

                    spdlog::info("----- Result : Win Check -----");

                    std::string dummy;
                    core::sqeuence pt;
                    for (auto &item : c)
                    {
                        pt.push_back({item.x, item.y});
                    }

                    switch (result)
                    {
                    case core::color::black:
                        spdlog::info("----- [ BLACK ] -----");
                        core::ai::shared->appendAI(pt, result);
                        std::cout << "Enter to continue..." << std::endl;
                        std::getline(std::cin, dummy);
                        this->clear();
                        break;
                    case core::color::white:
                        spdlog::info("----- [ WHITE ] -----");
                        core::ai::shared->appendAI(pt, result);
                        std::cout << "Enter to continue..." << std::endl;
                        std::getline(std::cin, dummy);
                        this->clear();
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
            }
        }
        break;
        }
    }

    bool setPredict(grc::point pos, int text = 0)
    {
        return std::static_pointer_cast<grc::gameBoard>(this->view[0])->setPredict(pos, 3, text);
    }

    bool setState(grc::point pos, int state)
    {
        return std::static_pointer_cast<grc::gameBoard>(this->view[0])->setState(pos, state);
    }

    void clear(int mode = 0, int predict = 1)
    {
        auto pts = std::static_pointer_cast<grc::gameBoard>(this->view[0]);
        pts->clear(mode);

        if (predict)
        {
            core::sqeuence pt;
            auto itemList = core::ai::shared->getNextNode(pt);

            for (int i = 0; i < itemList.size(); i++)
            {
                setPredict({itemList[i].point.x, itemList[i].point.y}, i + 1);
            }
        }
    }

    gameviewAIvsAIController()
    {
        setDesign();
    }

protected:
};
