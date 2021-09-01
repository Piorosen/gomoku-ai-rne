#pragma once
#define GL_SILENCE_DEPRECATION

#include <graphic/components/view.h>
#include <graphic/viewcontroller/viewcontroller.h>
#include <graphic/applicationdelegate.h>

#include <string>
#include <memory>
#include <optional>

namespace grc
{
    class application final
    {
    private:
        grc::size size = {500, 500};
        std::string title = "OpenGL : Test";
        std::shared_ptr<grc::viewcontroller> entryController = nullptr;

    public:
        static std::unique_ptr<grc::application> shared;

        std::unique_ptr<grc::applicationdelegate> delegate;

        void keyboard(unsigned char key, int x, int y) const;
        void mouse(int button, int state, int x, int y) const;
        void render() const;

        application();

        void run();
        void close();

        void setViewController(std::shared_ptr<grc::viewcontroller>&& vc);

        void initialize(const grc::size size, const std::string title);

        std::string getTitle() const;
        void setTitle(const std::string title);

        grc::size getSize() const;
        void setSize(const grc::size size);

    protected:
    };

    void glKeyboard(unsigned char key, int x, int y);
    void glMouse(int button, int state, int x, int y);
    void glDisplay();
}