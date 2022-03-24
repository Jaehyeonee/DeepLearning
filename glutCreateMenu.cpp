#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//오른쪽 버튼 클릭시 메뉴 glutCreateMenu 

GLboolean IsSphere = true;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.0, 0.5);
    if (IsSphere)                                           // following the ex--> IsSphere change true boolean so, we can draw Wire Sphere
        glutWireSphere(0.2, 15, 15);                        // drawing by wire sphere 
    else
        glutWireTorus(0.1, 0.3, 40, 20);                    // drawing torus
    glFlush();
}

void MyMainMenu(int entryID) {                              // when you select the menu option
    if (entryID == 1)                                       // execute the drawing action by true or false
        IsSphere = true;                                    // ex. when you click the 'Draw Sphere'    --> option id will be '1' --> 'true'
    else if (entryID == 2)
        IsSphere = false;
    else if (entryID == 3)
        exit(0);
    glutPostRedisplay();
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
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);        // glutCreateMenu : what kind of menu style 
    glutAddMenuEntry("Draw Sphere", 1);                     // when the menu select, saving the option number id 1 or 2 or 3
    glutAddMenuEntry("Draw Torus", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);                      // glutAttachMenu : adding menu options , GLUT_RIGHT_BUTTON: Right button of yout mouse
    glutDisplayFunc(MyDisplay);                             // MyDisplay 함수를 등록해두고, 
    glutMainLoop();                                         // glutMainLoop에 들어가면 execute. 
    return 0;   
}
