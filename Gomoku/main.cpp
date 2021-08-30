#include <graphic/application.h>
#include <graphic/components/imageview.h>
#include <graphic/utils/imagecollect.h>

#include <memory>
#include <spdlog/spdlog.h>
#include <glut.h>

std::shared_ptr<grc::viewcontroller> makeViewController()
{
    std::shared_ptr<grc::viewcontroller> entry = std::make_shared<grc::viewcontroller>();
    // view(grc::rect f, grc::color b)

    grc::rect f;
    f.location = {150, 0};
    f.size = {150, 150};
    grc::color c = grc::color(0xff0000ff);
    auto image = grc::imagecollect::shared->add("/Users/aoikazto/Desktop/gomoku.png");
    grc::rect f2;
    f2.location = {300, 150};
    f2.size = {150, 150};
    auto b = std::make_shared<grc::imageview>(f2);
    b->imageId = image;
    entry->view.push_back(std::make_shared<grc::view>(f, c));

    entry->view.push_back(std::static_pointer_cast<grc::view>(b));

    return entry;
}

int main(int argc, char **argv)
{
    grc::application::shared->initialize({500, 700}, "오목 : 그것이 알고 싶다.");
    auto p = makeViewController();
    grc::application::shared->entryController = p;
    grc::application::shared->run();
}
