#pragma once
#include <graphic/application.h>
#include <graphic/components/gameBoard.h>

#include <cstdlib>
#include <ctime>
#include <functional>

class gameViewController : public grc::viewcontroller
{
private:
    void setDesign()
    {
        grc::rect f1;
        f1.location = {0, 200};
        f1.size = {500, 500};

        grc::size s1 = {13, 13};
        view.push_back(std::make_shared<grc::gameBoard>(f1, s1));
    }

public:
    std::function<void(unsigned char)> buttonBack;
    virtual void keyboardEvent(unsigned char key, int x, int y) const override
    {
        if (buttonBack)
        {
            buttonBack(key);
        }
    }

    void newItem(int state)
    {
        grc::point pos = {rand() % 13, rand() % 13};
        std::static_pointer_cast<grc::gameBoard>(this->view[0])->setState(pos, state);
    }

    gameViewController()
    {
        srand((unsigned int)time(0));
        setDesign();
    }

protected:
};
