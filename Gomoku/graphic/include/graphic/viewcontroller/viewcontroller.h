#pragma once
#include <graphic/components/view.h>

namespace grc
{
    class viewcontroller
    {
    private:
    public:
        void render()
        {
            for (auto &v : view)
            {
                v->render();
            }
        }

        std::vector<std::shared_ptr<grc::view>> view;

    protected:
    };
}