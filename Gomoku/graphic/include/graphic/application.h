#pragma once

#define GL_SILENCE_DEPRECATION

#include <string>
#include <memory>

namespace grc
{
    class application
    {
    private:
    public:
        static std::unique_ptr<grc::application> shared;

        void keyboard(unsigned char key, int x, int y);
        void mouse(int button, int state, int x, int y);

        application(int width, int height, std::string title);
        application();

        void run();

    protected:
    };

    void glKeyboard(unsigned char key, int x, int y);
    void glMouse(int button, int state, int x, int y);
    void glDisplay();
}