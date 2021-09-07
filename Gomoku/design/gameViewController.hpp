#pragma once
#include <graphic/application.h>
#include <graphic/components/imageview.h>
#include <graphic/utils/imagecollect.h>
#include <graphic/components/imagebutton.h>
#include <graphic/components/gameBoard.h>

#include <cstdlib>
#include <ctime>
#include <functional>
#include <sstream>

class gameViewController : public grc::viewcontroller
{
private:
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
            if (this->boardChanged)
            {
                this->boardChanged(list);
            }
        };

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
                this->buttonBack(127);
            }
        };

        view.push_back(std::static_pointer_cast<grc::view>(p1));
        view.push_back(std::static_pointer_cast<grc::view>(p));
        view.push_back(std::static_pointer_cast<grc::view>(p2));
    }
    std::vector<std::string> split(std::string input, char delimiter)
    {
        std::vector<std::string> answer;
        std::stringstream ss(input);
        std::string temp;

        while (std::getline(ss, temp, delimiter))
        {
            answer.push_back(temp);
        }

        return answer;
    }
    std::string replace_all(
        std::string message,
        std::string pattern,
        std::string replace)
    {
        std::string result = message;
        std::string::size_type pos = 0;
        while ((pos = result.find(pattern)) != std::string::npos)
        {
            result.replace(pos, pattern.size(), replace);
        }
        return result;
    }

public:
    std::function<void(unsigned char)> buttonBack;
    std::function<void(std::vector<grc::point> *)> boardChanged;

    virtual void keyboardEvent(unsigned char key, int x, int y) const override
    {
        if (buttonBack)
        {
            buttonBack(key);
        }
    }
    bool setPredict(grc::point pos)
    {
        return std::static_pointer_cast<grc::gameBoard>(this->view[0])->setPredict(pos, 3);
    }

    bool setState(grc::point pos, int state)
    {
        return std::static_pointer_cast<grc::gameBoard>(this->view[0])->setState(pos, state);
    }

    void clear(int mode = 0)
    {
        auto pts = std::static_pointer_cast<grc::gameBoard>(this->view[0]);
        pts->clear(mode);
    }

    gameViewController()
    {
        srand((unsigned int)time(0));
        setDesign();
    }

protected:
};
