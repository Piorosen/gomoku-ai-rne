#include <graphic/application.h>
#include <memory>

int main(int argc, char **argv)
{
    grc::viewcontroller entry = grc::viewcontroller();
    // view(grc::rect f, grc::color b)
    grc::rect f;
    f.location = {150, 0};
    f.size = {150, 150};

    grc::color c = {40, 50, 0xff};
    entry.view.push_back(std::make_shared<grc::view>(f, c));

    grc::application::shared->entryController = &entry;
    grc::application::shared->run();
}
