#pragma once
#include <graphic/components/view.h>

namespace grc
{
    class viewcontroller
    {
    private:
    public:
        virtual void mouseEvent(int button, int state, int x, int y);
        virtual void keyboardEvent(unsigned char key, int x, int y);

        virtual void render() const;

        std::vector<std::shared_ptr<grc::view>> view;

    protected:
    };
}