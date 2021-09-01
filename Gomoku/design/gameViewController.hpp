#pragma once
#include <graphic/application.h>
#include <graphic/components/gameBoard.h>

#include <functional>

class gameViewController : public grc::viewcontroller
{
private:
    void setDesign()
    {
        grc::rect f1;
        f1.location = {0, 200};
        f1.size = {500, 500};
        view.push_back(std::make_shared<grc::gameBoard>(f1));
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

    gameViewController()
    {
    }

protected:
};
