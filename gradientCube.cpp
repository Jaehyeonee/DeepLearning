#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
 
// gradient cube graphic 

GLfloat MyVertices[8][3] = {        // 정점 리스트 저장
    { -0.25, -0.25, 0.25 },
    { -0.25, 0.25, 0.25 },
    { 0.25, 0.25, 0.25 },
    { 0.25, -0.25, 0.25 },
    { -0.25, -0.25, -0.25 },
    { -0.25, 0.25, -0.25 },
    { 0.25, 0.25, -0.25 },
    { 0.25, -0.25, -0.25 }
};
GLfloat MyColors[8][3] = {          // 정점에 따른 색칠 
    { 0.2, 0.2, 0.2 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 1.0 },
    { 0.0, 1.0, 1.0 }
};
GLubyte MyVertexList[24] = {        // 한 면에 대한 vertex 0,3,2,1로 이뤄진 면/ 2차원이 아닌 1차원 배열로 할당함. 
    0, 3, 2, 1,
    2, 3, 7, 6,
    0, 4, 7, 3,
    1, 2, 6, 5,
    4, 5, 6, 7,
    0, 1, 5, 4
};

void MyDisplay() {                  
    glClear(GL_COLOR_BUFFER_BIT);   
    glFrontFace(GL_CCW);                                 // 앞 부분만 보이겠다
    glEnable(GL_CULL_FACE);                              // 뒷 부분 활성화 하겠다 
    glEnableClientState(GL_COLOR_ARRAY);                 // 컬러 배열을 
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, MyColors);
    glVertexPointer(3, GL_FLOAT, 0, MyVertices);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(30.0, 1.0, 1.0, 1.0);                     // 30도 x,y,z축 회전
    for (GLint i = 0; i < 6; i++)                       // 6면체이므로 6개의 면을 그림 
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);      
        // 요소들을 가지고 polygon을 그리고, 4각형으로 그리고, 부호없는 2바이트로, 배열의 시작점 부터 4개씩 나눠서 
    glFlush();
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
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(MyDisplay);                 // MyDisplay 호출 
    glutMainLoop();
    return 0;
}
