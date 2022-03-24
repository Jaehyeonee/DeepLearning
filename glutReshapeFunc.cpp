#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);       //컬러버퍼에 초기화 색을 가함
    glColor3f(0.5, 0.5, 0.5);           //회색
    glBegin(GL_POLYGON);                //사각형
    glVertex3f(-0.5, -0.5, 0.0);    //좌하단 좌표
    glVertex3f(0.5, -0.5, 0.0);     //좌하단 좌표
    glVertex3f(0.5, 0.5, 0.0);      //우상단 좌표
    glVertex3f(-0.5, 0.5, 0.0);     //좌상단 좌표
    glEnd();
    glFlush();
}

void MyReshape(int NewWidth, int NewHeight) {       // 새 윈도우의 사이즈 변화 
    glViewport(0, 0, NewWidth, NewHeight);          // 
    GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)300; // 
    GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)300;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor,
        -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);      // 
    glutInitWindowSize(300, 300);       // 윈도우 사이즈
    glutInitWindowPosition(0, 0);       // display 시 윈도우의 모니터 위치 설정 : 왼쪽 위
    glutCreateWindow("OpenGL Example Drawing");
    glClearColor(1.0, 1.0, 1.0, 1.0);   // 초기화 색은 백색
    glutDisplayFunc(MyDisplay);         // 함수를 당장 호출되는게 아니라, 콜백 테이블에 기억만 ㅎ는 것
    glutReshapeFunc(MyReshape);         // ReshapeFunc라는 함수가 나오면 
                                        // MyReshape: 윈도우의 사이즈가 달라짐 
    glutMainLoop();                     // 이제부터 어떤 이벤트가 들어오는지 확인하겠다. (MyDisplay라는 이벤트가 있구나 호출하자)
    return 0;
}
