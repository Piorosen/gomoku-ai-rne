#include <graphic/application.h>

#if defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <spdlog/spdlog.h>

std::unique_ptr<grc::application> grc::application::shared = std::make_unique<grc::application>();

void grc::application::keyboard(unsigned char key, int x, int y) const
{
    this->entryController->keyboardEvent(key, x, y);

    //ESC 키가 눌러졌다면 프로그램 종료
    if (key == 27)
    {
        close();
    }
}

void grc::application::mouse(int button, int state, int x, int y) const
{
    if (this->entryController == nullptr)
    {
        spdlog::critical("Entry Controller Not Found");
        return;
    }
    else
    {
        this->entryController->mouseEvent(button, state, x, y);
    }
    // switch (button)
    // {
    // case GLUT_LEFT_BUTTON:
    //     if (this->entryController == nullptr)
    //     {
    //         spdlog::critical("Entry Controller Not Found");
    //         return;
    //     }
    //     else
    //     {
    //         this->entryController->mouseEvent(button, state, x, y);
    //     }
    //     break;
    // case GLUT_MIDDLE_BUTTON:
    //     break;
    // case GLUT_RIGHT_BUTTON:

    //     break;
    // default:
    //     break;
    // }
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
    spdlog::info("OpenGL Initialize : [{}, {}], {}", size.width, size.height, title);
    int myArgc = 0;
    glutInit(&myArgc, nullptr); //GLUT 초기화
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
}

std::string grc::application::getTitle() const
{
    return this->title;
}

void grc::application::setTitle(const std::string title)
{
    this->title = title;
    glutSetWindowTitle(title.c_str());
}

void grc::application::run()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutKeyboardFunc(grc::glKeyboard);
    glutMouseFunc(grc::glMouse);
    glutDisplayFunc(grc::glDisplay);

    glutMainLoop();
}

void grc::application::close() const
{
    glutDestroyWindow(glutGetWindow());

    if (this->closedEvent.has_value())
    {
        this->closedEvent.value()();
    }

    exit(0);
}

void grc::application::setViewController(std::shared_ptr<grc::viewcontroller> &&vc)
{
    this->entryController = vc;
    glutPostRedisplay();
}

void grc::application::initialize(const grc::size size, const std::string title)
{
    this->size = size;
    this->title = title;

    spdlog::info("OpenGL : run, [{}, {}, \"{}\"]", size.width, size.height, title);
    glutInitWindowSize(size.width, size.height); //윈도우의 width와 height
    glutCreateWindow(title.c_str());             //윈도우 생성
}

void grc::application::setSize(const grc::size size)
{
    this->size = size;
    glViewport(0, 0, size.width, size.height);
}

grc::size grc::application::getSize() const
{
    return this->size;
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
