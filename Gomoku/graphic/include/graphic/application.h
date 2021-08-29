#pragma once
#define GL_SILENCE_DEPRECATION

#include <graphic/components/view.h>
#include <graphic/viewcontroller/viewcontroller.h>

#include <string>
#include <memory>
#include <optional>

namespace grc
{
    class application
    {
    private:
    public:
        static std::unique_ptr<grc::application> shared;

        void keyboard(unsigned char key, int x, int y) const;
        void mouse(int button, int state, int x, int y) const;
        void render() const;

        application();

        void run();
        void close();

        grc::viewcontroller *entryController = nullptr;

    protected:
    };

    void glKeyboard(unsigned char key, int x, int y);
    void glMouse(int button, int state, int x, int y);
    void glDisplay();
}