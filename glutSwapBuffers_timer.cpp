#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <time.h>

// 타이머 콜백 함수

unsigned char PALETTE[16][3] = {
    { 255, 255, 255 },      // WHITE
    {   0, 255, 255 },      // CYAN
    { 255,   0, 255 },      // PURPLE
    {   0,   0, 255 },      // BLUE
    { 192, 192, 192 },      // LIGHT GRAY
    { 128, 128, 128 },      // DARK GRAY
    {   0, 128, 128 },      // DARK TEAL
    { 128,   0, 128 },      // DARK PURPLE
    {   0,   0, 128 },      // DARK BLUE
    { 255, 255,   0 },      // YELLOW
    {   0, 255,   0 },      // GREEN
    { 128, 128,   0 },      // DARK YELLOW
    {   0, 128,   0 },      // DARK GREEN
    { 255,   0,   0 },      // RED
    { 128,   0,   0 },      // DARK RED
    {   0,   0,   0 },      // BLACK
};

GLfloat Delta = 0.0;
GLint   Index = 0;
GLfloat Red = 0.0;
GLfloat Green = 0.0;
GLfloat Blue = 0.0;

void MyDisplay() {
    Red = PALETTE[Index][0] / 255.0f;
    Green = PALETTE[Index][1] / 255.0f;
    Blue = PALETTE[Index][2] / 255.0f;

    glColor3f(Red, Green, Blue);
    glBegin(GL_LINES);
    glVertex3f(-1.0 + Delta, 1.0, 0.0);
    glVertex3f(1.0 - Delta, -1.0, 0.0);
    glVertex3f(-1.0, -1.0 + Delta, 0.0);
    glVertex3f(1.0, 1.0 - Delta, 0.0);
    glEnd();
    glutSwapBuffers();                  // 버퍼 swap 함수
}

void MyTimer(int Value) {               // 형식적인 value 변수, 사용되는 부분이 없음. 
    if (Delta < 2.0f)                   // Delta : 사각형을 그릴 때 좌표 값을 증감 시키며 회전 하는 변수 
        Delta = Delta + 0.01;
    else {
        Delta = 0.0;
        if (++Index >= 15) {            // index 증가시키며, delta가 2를 넘으면, 인덱스가 15를 ㅓㅁ으면 (한바퀴 돌면) 그때 color값을 변경. 
            Index = 0;                  
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(10, MyTimer, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Timer Animation Sample");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutTimerFunc(10, MyTimer, 1);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
