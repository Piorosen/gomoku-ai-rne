#pragma once
#define GL_SILENCE_DEPRECATION

#include <string>
#include <map>
#include <optional>
#include <memory>

namespace grc
{
    class imagecollect
    {
    private:
        std::map<std::string, unsigned int> textureId;

    public:
        static std::unique_ptr<grc::imagecollect> shared;

        std::optional<int> get(std::string file);
        int add(std::string file);

    protected:
    };
}