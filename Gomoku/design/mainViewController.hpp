#pragma once
#include <graphic/application.h>
#include <graphic/components/imageview.h>
#include <graphic/components/button.h>
#include <graphic/components/imagebutton.h>
#include <graphic/utils/imagecollect.h>

std::shared_ptr<grc::view> makeMainMenuView()
{
    grc::rect f1;
    f1.location = {100, 137};
    f1.size = {300, 425};

    std::shared_ptr<grc::view> container = std::make_shared<grc::view>(f1, grc::color(0x992222ff));
    container->setHidden(true);

    grc::rect f2;
    f2.location = {125, 137 + 25};
    f2.size = {250, 75};
    auto newButton = std::make_shared<grc::button>(f2);

    grc::rect f3;
    f3.location = {125, 137 + 25 + 100 * 1};
    f3.size = {250, 75};
    auto continueButton = std::make_shared<grc::button>(f3);

    grc::rect f4;
    f4.location = {125, 137 + 25 + 100 * 2};
    f4.size = {250, 75};
    auto aimatchingButton = std::make_shared<grc::button>(f4);

    grc::rect f5;
    f5.location = {125, 137 + 25 + 100 * 3};
    f5.size = {250, 75};
    auto cancelButton = std::make_shared<grc::button>(f5);
    cancelButton->buttonDown = [container]()
    {
        container->setHidden(!container->getHidden());
    };

    container->controls.push_back(std::static_pointer_cast<grc::view>(newButton));
    container->controls.push_back(std::static_pointer_cast<grc::view>(continueButton));
    container->controls.push_back(std::static_pointer_cast<grc::view>(aimatchingButton));
    container->controls.push_back(std::static_pointer_cast<grc::view>(cancelButton));

    return container;
}

std::shared_ptr<grc::viewcontroller> makeMainViewController()
{
    std::shared_ptr<grc::viewcontroller> entry = std::make_shared<grc::viewcontroller>();
    auto logoIdx = grc::imagecollect::shared->add("./resources/logo.png");

    auto menu = makeMainMenuView();

    grc::rect f1;
    f1.location = {50, 50};
    f1.size = {400, 400};
    auto logo = std::make_shared<grc::imageview>(f1);
    logo->imageId = logoIdx;

    grc::rect f2;
    f2.location = {50, 475};
    f2.size = {400, 75};
    auto start = std::make_shared<grc::button>(f2);
    start->buttonDown = [menu]()
    {
        menu->setHidden(!menu->getHidden());
    };
    start->controls.push_back(menu);

    grc::rect f3;
    f3.location = {50, 575};
    f3.size = {400, 75};
    auto tree = std::make_shared<grc::button>(f3);
    tree->buttonDown = []() {};

    entry->view.push_back(std::static_pointer_cast<grc::view>(logo));
    entry->view.push_back(std::static_pointer_cast<grc::view>(start));
    entry->view.push_back(std::static_pointer_cast<grc::view>(tree));

    return entry;
}