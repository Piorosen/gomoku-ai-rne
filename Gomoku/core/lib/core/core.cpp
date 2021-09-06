#include <core/core.h>
#include <rapidjson/document.h>

std::unique_ptr<core::ai> core::ai::shared = std::make_unique<core::ai>();

void core::ai::newAI(std::string path)
{
}

void core::ai::loadAI(std::string path)
{
}

void core::ai::saveAI(std::string path)
{
}

void core::ai::appendAI(core::sqeuence sequence, core::color winner)
{
}