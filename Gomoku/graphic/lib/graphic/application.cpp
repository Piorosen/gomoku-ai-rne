#include <graphic/application.h>
#include <GLUT/glut.h>
#include <spdlog/spdlog.h>

void grc::application::keyboard(unsigned char key, int x, int y)
{
    spdlog::info("다음 키가 눌러졌습니다. \"{}\", \"{}\"", key, (int)key);

    //ESC 키가 눌러졌다면 프로그램 종료
    if (key == 27)
    {
        exit(0);
    }
}

void grc::application::mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    default:
        break;
    }
}
grc::application::application()
{
    application(500, 500, "hi!");
}

grc::application::application(int width, int height, std::string title)
{
    glutInit(nullptr, nullptr); //GLUT 초기화

    glutInitWindowSize(width, height); //윈도우의 width와 height
    glutCreateWindow(title.c_str());   //윈도우 생성

    glutKeyboardFunc(grc::glKeyboard);
    glutMouseFunc(grc::glMouse);

    // glutDisplayFunc(display);
}

void grc::glKeyboard(unsigned char key, int x, int y)
{
    grc::application::shared->keyboard(key, x, y);
}
void grc::glMouse(int button, int state, int x, int y)
{
    grc::application::shared->mouse(button, state, x, y);
}