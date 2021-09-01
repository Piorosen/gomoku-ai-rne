#include <graphic/application.h>
#include <graphic/components/imageview.h>
#include <graphic/components/button.h>

#include <graphic/utils/imagecollect.h>

#include <memory>
#include <spdlog/spdlog.h>
#include <glut.h>

std::shared_ptr<grc::viewcontroller> makeViewController()
{
    std::shared_ptr<grc::viewcontroller> entry = std::make_shared<grc::viewcontroller>();
    // view(grc::rect f, grc::color b)

    auto image = grc::imagecollect::shared->add("/Users/aoikazto/Desktop/aaaa.jpg");
    grc::rect f2;
    f2.location = {0, 0};
    f2.size = {150, 150};
    auto b = std::make_shared<grc::imageview>(f2);
    b->imageId = image;

    grc::rect f3;
    f3.location = {150, 0};
    f3.size = {150, 150};
    auto c = std::make_shared<grc::view>(f3, grc::color(0xff6655ff));

    grc::rect f4;
    f4.location = {0, 150};
    f4.size = {150, 150};
    auto d = std::make_shared<grc::button>(f4);

    entry->view.push_back(std::static_pointer_cast<grc::view>(b));
    entry->view.push_back(c);
    entry->view.push_back(std::static_pointer_cast<grc::view>(d));

    return entry;
}

int main(int argc, char **argv)
{
    grc::application::shared->initialize({500, 700}, "오목 : 그것이 알고 싶다.");
    auto p = makeViewController();
    grc::application::shared->entryController = p;
    grc::application::shared->run();
}
