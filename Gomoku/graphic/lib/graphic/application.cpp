#include <graphic/application.h>
#include <GLUT/glut.h>
#include <spdlog/spdlog.h>

std::unique_ptr<grc::application> grc::application::shared = std::make_unique<grc::application>();

void grc::application::keyboard(unsigned char key, int x, int y) const
{
    spdlog::info("keyboard event : [{}, {}]", (char)key, (int)key);

    //ESC 키가 눌러졌다면 프로그램 종료
    if (key == 27)
    {
        exit(0);
    }
}

void grc::application::mouse(int button, int state, int x, int y) const
{
    spdlog::info("mouse event : [{}, {}, {}, {}]", button, state, x, y);

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

void grc::application::render() const
{
    if (this->entryController == nullptr)
    {
        spdlog::critical("Entry Controller Not Found");
        return;
    }
    else
    {
        this->entryController->render();
    }
}

grc::application::application()
{
    int width = 500;
    int height = 500;
    std::string title = "hello!";
    spdlog::info("OpenGL Initialize : [{}, {}], {}", width, height, title);
    int myArgc = 0;
    glutInit(&myArgc, nullptr); //GLUT 초기화

    glutInitWindowSize(width, height); //윈도우의 width와 height
    glutCreateWindow(title.c_str());   //윈도우 생성

    glutKeyboardFunc(grc::glKeyboard);
    glutMouseFunc(grc::glMouse);
    glutDisplayFunc(grc::glDisplay);
}

void grc::application::run()
{
    glutMainLoop();
}

void grc::application::close()
{
}

void grc::glDisplay()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //glClear에서 컬러 버퍼 지운 후 윈도우를 채울 색을 지정, 검은색
    glClear(GL_COLOR_BUFFER_BIT);         //컬러 버퍼를 지운다.
    glLoadIdentity();

    grc::application::shared->render();

    glutSwapBuffers();
}

void grc::glKeyboard(unsigned char key, int x, int y)
{
    grc::application::shared->keyboard(key, x, y);
}
void grc::glMouse(int button, int state, int x, int y)
{
    grc::application::shared->mouse(button, state, x, y);
}