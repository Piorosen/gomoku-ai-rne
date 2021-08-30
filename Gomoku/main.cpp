#include <graphic/application.h>
#include <memory>
#include <spdlog/spdlog.h>

int main(int argc, char **argv)
{
    std::shared_ptr<grc::viewcontroller> entry = std::make_shared<grc::viewcontroller>();
    // view(grc::rect f, grc::color b)

    grc::rect f;
    f.location = {150, 0};
    f.size = {150, 150};
    grc::color c = grc::color(0xffffffff);

    entry->view.push_back(std::make_shared<grc::view>(f, c));

    grc::application::shared->initialize({500, 700}, "오목 : 그것이 알고 싶다.");
    grc::application::shared->entryController = entry;
    grc::application::shared->run();
}
