#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//마우스 클릭에 따른 사각형 동적 그리기

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

void MyDisplay() {
    glViewport(0, 0, 300, 300);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(TopLeftX / 300.0, (300 - TopLeftY) / 300.0, 0.0);        // 사각형의 좌표가 아래에서 다 이뤄지면 그 때 그려라 
    glVertex3f(TopLeftX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
    glVertex3f(BottomRightX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
    glVertex3f(BottomRightX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
    glEnd();
    glFlush();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) { // 마우스클릭 이루어지면 발생 
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {     // 왼쪽 버튼을 클릭하고 눌러진 상태이면 
        TopLeftX = X;                                           // 현재 값을 x, y 로 설정해라
        TopLeftY = Y;
    }
}

void MyMouseMove(GLint X, GLint Y) {                            // 클릭이 이루어진 후 무브가 이루어지면
    BottomRightX = X;                                           // 좌표 설정 
    BottomRightY = Y;
    glutPostRedisplay();                                        // 이후 다시 display를 다시 불러라 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Drawing Example");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(MyDisplay);             // 제일처음으로 저장되는 mydisplay 함수, 제일 먼저 윈도우를 그리게 됨 > 아무것도 그려지지 않음
    glutMouseFunc(MyMouseClick);            // 마우스 클릭이 이루어지면 
    glutMotionFunc(MyMouseMove);            // 마우스가 움직이면 콜백테이블에 mymousemove함수를 저장하고 
    glutMainLoop();
    return 0;
}
