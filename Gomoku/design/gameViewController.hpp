#pragma once
#include <graphic/application.h>
#include <graphic/components/imageview.h>
#include <graphic/components/button.h>
#include <graphic/components/imagebutton.h>
#include <graphic/utils/imagecollect.h>

std::shared_ptr<grc::viewcontroller> makeGameViewController()
{
    std::shared_ptr<grc::viewcontroller> entry = std::make_shared<grc::viewcontroller>();

    return entry;
}