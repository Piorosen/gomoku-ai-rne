#include <graphic/utils/imagecollect.h>
#include <GLUT/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <spdlog/spdlog.h>

std::unique_ptr<grc::imagecollect> grc::imagecollect::shared = std::make_unique<grc::imagecollect>();

int grc::imagecollect::add(std::string file)
{
    int width, height, channels;

    auto buffer = stbi_load(file.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (buffer == nullptr)
    {
        spdlog::critical("image load fail : \"{}\"", file);
    }
    else
    {
        spdlog::info("load image : [{}, {}, {}]", width, height, channels);
    }
    GLuint texture;
    glGenTextures(1, &texture);
    //텍스처 ID를 바인딩 -  사용할 텍스처 차원을 지정해준다.
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, STBI_rgb_alpha, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(buffer);
    textureId[file] = texture;
    return texture;
}

std::optional<int> grc::imagecollect::get(std::string file)
{
    if (textureId.find(file) != textureId.end())
    {
        return std::optional<int>(textureId[file]);
    }
    else
    {
        return std::nullopt;
    }
}
