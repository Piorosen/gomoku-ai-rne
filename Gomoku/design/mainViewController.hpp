#pragma once
#include <graphic/application.h>
#include <graphic/components/imageview.h>
#include <graphic/components/button.h>
#include <graphic/components/imagebutton.h>
#include <graphic/utils/imagecollect.h>

std::shared_ptr<grc::view> makeMainMenuView()
{
    auto aiIdx = grc::imagecollect::shared->add("./resources/ai.png");
    auto closeIdx = grc::imagecollect::shared->add("./resources/close.png");
    auto newIdx = grc::imagecollect::shared->add("./resources/new.png");
    auto continueIdx = grc::imagecollect::shared->add("./resources/continue.png");

    auto ai_focusIdx = grc::imagecollect::shared->add("./resources/ai_focus.png");
    auto close_focusIdx = grc::imagecollect::shared->add("./resources/close_focus.png");
    auto new_focusIdx = grc::imagecollect::shared->add("./resources/new_focus.png");
    auto continue_focusIdx = grc::imagecollect::shared->add("./resources/continue_focus.png");

    grc::rect f1;
    f1.location = {100, 137};
    f1.size = {300, 425};

    std::shared_ptr<grc::view> container = std::make_shared<grc::view>(f1, grc::color(0xffffffff));
    container->setHidden(true);
    container->setBorder(3, grc::color(0x000000ff));

    grc::rect f2;
    f2.location = {125, 137 + 25};
    f2.size = {250, 75};
    auto newButton = std::make_shared<grc::imagebutton>(f2);
    newButton->backgroundImageId = newIdx;
    newButton->focusImageId = new_focusIdx;

    grc::rect f3;
    f3.location = {125, 137 + 25 + 100 * 1};
    f3.size = {250, 75};
    auto continueButton = std::make_shared<grc::imagebutton>(f3);
    continueButton->backgroundImageId = continueIdx;
    continueButton->focusImageId = continue_focusIdx;

    grc::rect f4;
    f4.location = {125, 137 + 25 + 100 * 2};
    f4.size = {250, 75};
    auto aimatchingButton = std::make_shared<grc::imagebutton>(f4);
    aimatchingButton->backgroundImageId = aiIdx;
    aimatchingButton->focusImageId = ai_focusIdx;

    grc::rect f5;
    f5.location = {125, 137 + 25 + 100 * 3};
    f5.size = {250, 75};
    auto cancelButton = std::make_shared<grc::imagebutton>(f5);
    cancelButton->backgroundImageId = closeIdx;
    cancelButton->focusImageId = close_focusIdx;

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

    auto continueIdx = grc::imagecollect::shared->add("./resources/start.png");
    auto continue_focusIdx = grc::imagecollect::shared->add("./resources/start_focus.png");

    auto treeIdx = grc::imagecollect::shared->add("./resources/tree.png");
    auto tree_focusIdx = grc::imagecollect::shared->add("./resources/tree_focus.png");

    auto menu = makeMainMenuView();

    grc::rect f1;
    f1.location = {50, 50};
    f1.size = {400, 400};
    auto logo = std::make_shared<grc::imageview>(f1);
    logo->imageId = logoIdx;

    grc::rect f2;
    f2.location = {50, 475};
    f2.size = {400, 75};
    auto start = std::make_shared<grc::imagebutton>(f2);
    start->buttonDown = [menu]()
    {
        menu->setHidden(!menu->getHidden());
    };
    start->controls.push_back(menu);
    start->backgroundImageId = continueIdx;
    start->focusImageId = continue_focusIdx;

    grc::rect f3;
    f3.location = {50, 575};
    f3.size = {400, 75};
    auto tree = std::make_shared<grc::imagebutton>(f3);
    tree->buttonDown = []() {};
    tree->backgroundImageId = treeIdx;
    tree->focusImageId = tree_focusIdx;

    grc::rect f4;
    f4.location = {0, 0};
    f4.size = grc::application::shared->getSize();

    entry->view.push_back(std::make_shared<grc::view>(f4, grc::color(0xffffffff)));
    entry->view.push_back(std::static_pointer_cast<grc::view>(logo));
    entry->view.push_back(std::static_pointer_cast<grc::view>(start));
    entry->view.push_back(std::static_pointer_cast<grc::view>(tree));

    return entry;
}