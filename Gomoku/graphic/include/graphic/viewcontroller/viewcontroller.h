#pragma once
#include <graphic/components/view.h>

namespace grc
{
    class viewcontroller
    {
    private:
    public:
        void mouseEvent(int button, int state, int x, int y);

        virtual void render() const;

        std::vector<std::shared_ptr<grc::view>> view;

    protected:
    };
}