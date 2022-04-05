#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// 복잡한 그림을 그릴 때 call하여 사용가능

int MyListID;

void MyCreateList() {                   // 그림을 그려서 MyListID에 저장 
    MyListID = glGenLists(1);
    glNewList(MyListID, GL_COMPILE);
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.0);        // 사각형 그림
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
    glEndList();                        
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);       
    glViewport(0, 0, 300, 300);     
    glCallList(MyListID);               // 여기서 호출해서 컴파일된 사각형이 그려짐
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Example Drawing");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
    glutDisplayFunc(MyDisplay);
    MyCreateList();                             // 그림을 그리진 않음
    glutMainLoop();
    return 0;
}
