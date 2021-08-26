#include <graphic/application.h>
#include <GLUT/glut.h>
#include <spdlog/spdlog.h>

std::unique_ptr<grc::application> grc::application::shared = std::make_unique<grc::application>();

void grc::application::keyboard(unsigned char key, int x, int y)
{
    spdlog::info("keyboard event : [{}, {}]", (char)key, (int)key);

    //ESC 키가 눌러졌다면 프로그램 종료
    if (key == 27)
    {
        exit(0);
    }
}

void grc::application::mouse(int button, int state, int x, int y)
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

grc::application::application()
{
    application(500, 500, "hi!");
}

grc::application::application(int width, int height, std::string title)
{

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

void grc::glDisplay()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //glClear에서 컬러 버퍼 지운 후 윈도우를 채울 색을 지정, 검은색
    glClear(GL_COLOR_BUFFER_BIT);         //컬러 버퍼를 지운다.
    glLoadIdentity();

    glColor3f(1.0f, 0.0f, 0.0f); //빨간색 지정
    glBegin(GL_QUADS);           //4점이 하나의 사각형을 구성한다. 반시계 방향으로 4점의 vertex를 지정해줘야 한다.
    glVertex2f(-0.5f, -0.5f);    // x, y
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); //흰색 지정

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