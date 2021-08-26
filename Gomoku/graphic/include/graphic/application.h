#pragma once

#define GL_SILENCE_DEPRECATION

#include <graphic/applicationdelegate.h>
#include <string>
#include <memory>

namespace grc
{
    class application
    {
    private:
    public:
        static std::unique_ptr<grc::application> shared;

        void keyboard(unsigned char key, int x, int y);
        void mouse(int button, int state, int x, int y);

        application(int width, int height, std::string title);
        application();

    protected:
    };

    void glKeyboard(unsigned char key, int x, int y);
    void glMouse(int button, int state, int x, int y);
}

auto grc::application::shared = std::make_unique<grc::application>();
// void drawBitmapText(char *str, float x, float y, float z)
// {
//     glRasterPos3f(x, y, z); //문자열이 그려질 위치 지정

//     while (*str)
//     {
//         //GLUT_BITMAP_TIMES_ROMAN_24 폰트를 사용하여 문자열을 그린다.
//         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);

//         str++;
//     }
// }

// void display()
// {
//     glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //glClear에서 컬러 버퍼 지운 후 윈도우를 채울 색을 지정, 검은색
//     glClear(GL_COLOR_BUFFER_BIT);         //컬러 버퍼를 지운다.
//     glLoadIdentity();

//     //중앙이 원점에 오도록 한변의 길이가 1인 빨간색 정사각형을 그린다.
//     glColor3f(1.0f, 0.0f, 0.0f); //빨간색 지정
//     glBegin(GL_QUADS);           //4점이 하나의 사각형을 구성한다. 반시계 방향으로 4점의 vertex를 지정해줘야 한다.
//     glVertex2f(-0.5f, -0.5f);    // x, y
//     glVertex2f(0.5f, -0.5f);
//     glVertex2f(0.5f, 0.5f);
//     glVertex2f(-0.5f, 0.5f);
//     glEnd();

//     glColor3f(1.0f, 1.0f, 1.0f);                      //흰색 지정
//     drawBitmapText("-0.5, -0.5", -0.5f, -0.5f, 0.0f); // 지정한 좌표에 문자열 출력
//     drawBitmapText("0.5, -0.5", 0.5f, -0.5f, 0.0f);
//     drawBitmapText("0.5, 0.5", 0.5f, 0.5f, 0.0f);
//     drawBitmapText("-0.5, 0.5", -0.5f, 0.5f, 0.0f);

//     //더블 버퍼링을 하고 있다면, 프론트 버퍼와 백 버퍼 2개가 사용된다.현재 화면에 보여지는 것은 프론트 버퍼에 있는 내용이다.
//     //백 버퍼는 다음 장면을 위해 렌더링을 하고 있는 곳이다.백 버퍼의 렌더링이 완료되면 두 개의 버퍼를 교환(swap)한다.
//     //화면에 업데이트된 프론트 버퍼에 있는 내용이 출력된다.

//     //싱글 버퍼라면 버퍼에 있는 것을 화면에 출력한다.
//     glutSwapBuffers();
// }

// int start(int argc, char **argv)
// {
//     glutInit(&argc, argv); //GLUT 초기화

//     glutInitWindowSize(500, 500);       //윈도우의 width와 height
//     glutInitWindowPosition(100, 100);   //윈도우의 위치 (x,y)
//     glutCreateWindow("OpenGL Example"); //윈도우 생성

//     //디스플레이 콜백 함수 등록, display함수는 윈도우 처음 생성할 때와 화면 다시 그릴 필요 있을때 호출된다.
//     glutDisplayFunc(display);
//     //키보드 콜백 함수 등록, 키보드가 눌러지면 호출된다.
//     glutKeyboardFunc(keyboard);

//     //GLUT event processing loop에 진입한다.
//     //이 함수는 리턴되지 않기 때문에 다음줄에 있는 코드가 실행되지 않는다.
//     glutMainLoop();

//     return 0;
// }