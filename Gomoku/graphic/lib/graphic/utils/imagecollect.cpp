#include <graphic/utils/imagecollect.h>
#include <GLUT/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::unique_ptr<grc::imagecollect> grc::imagecollect::shared = std::make_unique<grc::imagecollect>();

int grc::imagecollect::add(std::string file)
{
    int width, height, channels;
    auto buffer = stbi_load(file.c_str(), &width, &height, &channels, 0);
    if (buffer == nullptr)
    {
        printf(">???");
    }
    GLuint texture;
    glGenTextures(1, &texture);
    //텍스처 ID를 바인딩 -  사용할 텍스처 차원을 지정해준다.
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
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
