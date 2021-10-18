#pragma once
#include <graphic/application.h>
#include <graphic/components/imageview.h>
#include <graphic/utils/imagecollect.h>
#include <graphic/components/imagebutton.h>
#include <graphic/components/gameBoard.h>

#include <core/core.h>

#include <random>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <sstream>

class gameViewHumanvsAIController : public grc::viewcontroller
{
private:
    std::shared_ptr<grc::gameBoard> board;
    core::color aiTern = core::color::none;
    std::shared_ptr<grc::imageview> winView;
    std::shared_ptr<grc::view> winContainer;

    void showWinView(core::color color)
    {
        auto black_victoryIdx = grc::imagecollect::shared->get("./resources/black_victory.png");
        auto white_victoryIdx = grc::imagecollect::shared->get("./resources/white_victory.png");

        if (color == core::color::black)
        {
            winView->imageId = black_victoryIdx;
            winContainer->setHidden(false);
        }
        else if (color == core::color::white)
        {
            winView->imageId = white_victoryIdx;
            winContainer->setHidden(false);
        }
    }

    std::shared_ptr<grc::view> makeVictoryView()
    {
        auto okIdx = grc::imagecollect::shared->add("./resources/ok.png");
        auto ok_focusIdx = grc::imagecollect::shared->add("./resources/ok_focus.png");
        auto black_victoryIdx = grc::imagecollect::shared->add("./resources/black_victory.png");
        auto white_victoryIdx = grc::imagecollect::shared->add("./resources/white_victory.png");

        grc::rect f1;
        f1.location = {100, 175};
        f1.size = {300, 350};
        winContainer = std::make_shared<grc::view>(f1, grc::color(0xffffffff));
        // container->setHidden(true);
        winContainer->setBorder(10, grc::color(0x000000ff));

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
        okButton->buttonDown = [this]()
        {
            this->clear();
            winContainer->setHidden(true);
        };

        winContainer->controls.push_back(std::static_pointer_cast<grc::view>(winView));
        winContainer->controls.push_back(std::static_pointer_cast<grc::view>(okButton));

        return winContainer;
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
        auto p1 = std::make_shared<grc::gameBoard>(f1, s1);

        p1->boardChanged = [this](std::vector<grc::point> *list)
        {
            // 홀 : 백 차례
            // 짝 : 흑 차례
            core::sqeuence seq;
            for (auto &item : *list)
            {
                seq.push_back({item.x, item.y});
            }

            if (list->size() % 2 == 1 && aiTern == core::color::white)
            {
                // AI 백 모드
                auto itemList = core::ai::shared->getNextNode(seq);
                int random = std::random_device{}() % 3;
                int idx = std::min((int)itemList.size() - 1, random);
                seq.push_back(itemList[idx].point);
                board->setState({itemList[idx].point.x, itemList[idx].point.y}, 2);
            }
            else if (list->size() % 2 == 0 && aiTern == core::color::black)
            {
                // AI 흑 모드
                auto itemList = core::ai::shared->getNextNode(seq);
                int random = std::random_device{}() % 3;
                int idx = std::min((int)itemList.size() - 1, random);
                seq.push_back(itemList[idx].point);
                board->setState({itemList[idx].point.x, itemList[idx].point.y}, 1);
            }
        };
        board = p1;

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

        view.push_back(std::static_pointer_cast<grc::view>(p1));
        view.push_back(std::static_pointer_cast<grc::view>(p));
        view.push_back(std::static_pointer_cast<grc::view>(p2));

        auto menu = this->makeVictoryView();
        view.push_back(menu);
    }

    std::function<core::color(std::vector<std::vector<core::color>>)> winCheck;

public:
    std::function<void()> buttonBack;
    std::function<std::optional<grc::point>(std::vector<grc::point> *list, core::color color)> nextAi;

    virtual void keyboardEvent(unsigned char key, int x, int y) override
    {
        switch (key)
        {
        case 27:
        {
            if (buttonBack)
            {
                buttonBack();
            }
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
        }
    }

    void setWinCheck(core::color (*check)(std::vector<std::vector<core::color>>))
    {
        this->winCheck = check;
    }

    void setWinCheck(std::function<core::color(std::vector<std::vector<core::color>>)> check)
    {
        this->winCheck = check;
    }

    bool setPredict(grc::point pos, int text = 0)
    {
        return std::static_pointer_cast<grc::gameBoard>(this->view[0])->setPredict(pos, 3, text);
    }

    bool setState(grc::point pos, int state)
    {
        return std::static_pointer_cast<grc::gameBoard>(this->view[0])->setState(pos, state);
    }

    void clear(int mode = 0)
    {
        auto pts = std::static_pointer_cast<grc::gameBoard>(this->view[0]);
        pts->clear(mode);
        board->setAutoColorChange(false, !((int)this->aiTern));

        // if (aiTern == core::color::black)
        // {
        //     auto itemList = core::ai::shared->getNextNode(core::sqeuence());
        //     int random = std::random_device{}() % 3;
        //     int idx = std::min((int)itemList.size() - 1, random);
        //     board->setState({itemList[idx].point.x, itemList[idx].point.y}, 1);
        // }
    }

    void setAiTern(core::color c)
    {
        this->aiTern = c;
        board->setAutoColorChange(false, !((int)c));
        // AI 흑 모드
    }

    gameViewHumanvsAIController()
    {
        setDesign();
    }

protected:
};
