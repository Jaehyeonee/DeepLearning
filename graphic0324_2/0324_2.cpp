/* simple painting program with text, lines, triangles,
rectangles, and points */

#define NULL 0
#define LINE 1
#define RECTANGLE 2
#define TRIANGLE 3
#define PPOINTSS 4
#define TEXTT 5

#include <GL/freeglut.h>
#include <stdlib.h>

void mymouse(int, int, int, int);
void key(unsigned char, int, int);

void drawSquare(int, int);
void myReshape(GLsizei, GLsizei);
void mydisplay(void);
void myinit();

void screen_box(int, int, int);
void right_menu(int);
void middle_menu(int);
void color_menu(int);
void pixel_menu(int);
void fill_menu(int);
int pick(int, int);

/* globals */

GLsizei wh = 500, ww = 500; /* initial window size */		
GLfloat size = 3.0;   /* half side length of square */
int draw_mode = 0; /* drawing mode */
int rx, ry; /*raster position*/

GLfloat r = 1.0, g = 1.0, b = 1.0; /* drawing color */
int fill = 0; /* fill flag */

void drawSquare(int x, int y)
{
	y = wh - y;
	glColor3ub((char)rand() % 256, (char)rand() % 256, (char)rand() % 256);
	glBegin(GL_POLYGON);
	glVertex2f(x + size, y + size);
	glVertex2f(x - size, y + size);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);
	glEnd();
}


/* reshaping routine called whenever window is resized or moved */

void myReshape(GLsizei w, GLsizei h)
{

	/* adjust clipping box */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* adjust viewport and clear */

	glViewport(0, 0, w, h);
	glClearColor((GLclampf)0.8, (GLclampf)0.8, (GLclampf)0.8, (GLclampf)1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	/* set global size for use by drawing routine */

	ww = w;
	wh = h;
}

void myinit()
{

	glViewport(0, 0, ww, wh);


	/* Pick 2D clipping window to match size of X window. This choice
	avoids having to scale object coordinates each time window is
	resized. */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)ww, 0.0, (GLdouble)wh, -1.0, 1.0);

	/* set clear color to black and clear window */

	glClearColor((GLclampf)0.8, (GLclampf)0.8, (GLclampf)0.8, (GLclampf)1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void mymouse(int btn, int state, int x, int y)
{
	static int count;
	int where;
	static int xp[2], yp[2];
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		where = pick(x, y);
		glColor3f(r, g, b);
		if (where != 0)					// where=0이면 그림을 그리겠다 , 0이 아니면 메뉴가 선택되었다--> 새로운 그림이 그려져야 함
		{								// where 아래 0 
			count = 0;					// 초기화
			draw_mode = where;			// draw_mode setting
		}
		else switch (draw_mode)
		{
		case(LINE):
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				glBegin(GL_LINES);
				glVertex2i(x, wh - y);
				glVertex2i(xp[0], wh - yp[0]);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;


		case(RECTANGLE):
			if (count == 0)
			{
				count++;
				xp[0] = x;
				yp[0] = y;
			}
			else
			{
				if (fill) glBegin(GL_POLYGON);
				else glBegin(GL_LINE_LOOP);
				glVertex2i(x, wh - y);
				glVertex2i(x, wh - yp[0]);
				glVertex2i(xp[0], wh - yp[0]);
				glVertex2i(xp[0], wh - y);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		case (TRIANGLE):
			switch (count)
			{
			case(0):
				count++;
				xp[0] = x;
				yp[0] = y;
				break;
			case(1):
				count++;
				xp[1] = x;
				yp[1] = y;
				break;
			case(2):
				if (fill) glBegin(GL_POLYGON);
				else glBegin(GL_LINE_LOOP);
				glVertex2i(xp[0], wh - yp[0]);
				glVertex2i(xp[1], wh - yp[1]);
				glVertex2i(x, wh - y);
				glEnd();
				draw_mode = 0;
				count = 0;
			}
			break;
		case(PPOINTSS):
		{
			drawSquare(x, y);
			count++;
		}
		break;
		case(TEXTT):
		{
			rx = x;
			ry = wh - y;
			glRasterPos2i(rx, ry);
			count = 0;
		}
		}   /* endelse*/
	}/*endif*/
	glPopAttrib();								// 메뉴를 선택한 후에는 그림을 그려지는게 아니고 mode만 세팅 됨 따라서 마우스를 한번더 클릭해야됨 그러면 my mouse 다시 또 어딜 클릭했는지 호출됨 
	glFlush();								 	// 
}

int pick(int x, int y)							// 클릭시 모니터의 클릭 위치 값이 들어옴
{
	y = wh - y;									// y 값을 gl의 값으로 변경 ???
	if (y < wh - ww / 10) return 0;
	else if (x < ww / 10) return LINE;			// 메뉴의 영역을 나눔 
	else if (x < ww / 5) return RECTANGLE;
	else if (x < 3 * ww / 10) return TRIANGLE;
	else if (x < 2 * ww / 5) return PPOINTSS;
	else if (x < ww / 2) return TEXTT;
	else return 0;								// 전체에서 메뉴의 사각형을 뺀 나머지 부분은 다 display 영역
}

void screen_box(int x, int y, int s)
{
	glBegin(GL_QUADS);
	glVertex2i(x, y);					// 좌 하향 
	glVertex2i(x + s, y);				// 우 하향
	glVertex2i(x + s, y + s);			// 우 상향
	glVertex2i(x, y + s);				// 좌 상향 
	glEnd();
}

void right_menu(int id)
{
	if (id == 1) exit(0);
	else
	{
		glClearColor((GLclampf)0.8, (GLclampf)0.8, (GLclampf)0.8, (GLclampf)1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		mydisplay();
	}
}

void middle_menu(int id)
{
	// middle 버튼을 누르면 mymouse를 호출하지만 mymouse안에 middle에 대한 게 없으니가
}

void color_menu(int id)
{
	if (id == 1) { r = 1.0; g = 0.0; b = 0.0; }
	else if (id == 2) { r = 0.0; g = 1.0; b = 0.0; }
	else if (id == 3) { r = 0.0; g = 0.0; b = 1.0; }
	else if (id == 4) { r = 0.0; g = 1.0; b = 1.0; }
	else if (id == 5) { r = 1.0; g = 0.0; b = 1.0; }
	else if (id == 6) { r = 1.0; g = 1.0; b = 0.0; }
	else if (id == 7) { r = 1.0; g = 1.0; b = 1.0; }
	else if (id == 8) { r = 0.0; g = 0.0; b = 0.0; }
}

void pixel_menu(int id)
{
	if (id == 1) size = 2 * size;
	else if (size > 1) size = size / 2;
}

void fill_menu(int id)
{
	if (id == 1) fill = 1;
	else fill = 0;
}

void key(unsigned char k, int xx, int yy)
{
	if (draw_mode != TEXTT) return;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(rx, ry);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
	/*glutStrokeCharacter(GLUT_STROKE_ROMAN,i); */
	rx += glutBitmapWidth(GLUT_BITMAP_9_BY_15, k);

}

void mydisplay(void)
{
	int shift = 0;

	glColor3f(1.0, 1.0, 1.0);
	screen_box(0, wh - ww / 10, ww / 10);					// line box: window size 바뀔 때마다 reshape (x= 40, size 50)
	glColor3f(1.0, 0.0, 0.0);
	screen_box(ww / 10, wh - ww / 10, ww / 10);				// rectangle box : 
	glColor3f(0.0, 1.0, 0.0);
	screen_box(ww / 5, wh - ww / 10, ww / 10);				// triangle box
	glColor3f(0.0, 0.0, 1.0);
	screen_box(3 * ww / 10, wh - ww / 10, ww / 10);			// point	
	glColor3f(1.0, 1.0, 0.0);
	screen_box(2 * ww / 5, wh - ww / 10, ww / 10);			// string
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(wh / 40, wh - ww / 20);
	glVertex2i(wh / 40 + ww / 20, wh - ww / 20);
	glEnd();

	screen_box(ww / 10 + ww / 40, wh - ww / 10 + ww / 40, ww / 20);

	glBegin(GL_TRIANGLES);
	glVertex2i(ww / 5 + ww / 40, wh - ww / 10 + ww / 40);
	glVertex2i(ww / 5 + ww / 20, wh - ww / 40);
	glVertex2i(ww / 5 + 3 * ww / 40, wh - ww / 10 + ww / 40);
	glEnd();
	glPointSize(3.0);

	glBegin(GL_POINTS);
	glVertex2i(3 * ww / 10 + ww / 20, wh - ww / 20);
	glEnd();
	glRasterPos2i(2 * ww / 5, wh - ww / 20);				// 위치 지정 glRasterPos2i() , 
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');			// 글씨(이미지)가 출력됨 glutBitmapCharacter '글씨 사이즈를 9by15 크기의 bitmap으로'
	shift = glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');		// bitmap의 너비를 구해서 shift변수에 넣어라 glutBitmapWidth()	
	glRasterPos2i(2 * ww / 5 + shift, wh - ww / 20);		// A를 썼던 위치를 밀어서 너비만큼 옮기고 그 위치에 B를 써라
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');			
	shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');		// width를 구해서 shift에 더하기 
	glRasterPos2i(2 * ww / 5 + shift, wh - ww / 20);	
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glFlush();

}


int main(int argc, char** argv)
{
	int c_menu, p_menu, f_menu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("square");
	c_menu = glutCreateMenu(color_menu);			//선택한 값이 c_menu에 값을 전달 
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Cyan", 4);
	glutAddMenuEntry("Magenta", 5);
	glutAddMenuEntry("Yellow", 6);
	glutAddMenuEntry("White", 7);
	glutAddMenuEntry("Black", 8);
	p_menu = glutCreateMenu(pixel_menu);
	glutAddMenuEntry("increase pixel size", 1);
	glutAddMenuEntry("decrease pixel size", 2);
	f_menu = glutCreateMenu(fill_menu);
	glutAddMenuEntry("fill on", 1);
	glutAddMenuEntry("fill off", 2);
	glutCreateMenu(right_menu);					// right menu
	glutAddMenuEntry("quit", 1);
	glutAddMenuEntry("clear", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutCreateMenu(middle_menu);				// middle menu 
	glutAddSubMenu("Colors", c_menu);
	glutAddSubMenu("Pixel Size", p_menu);
	glutAddSubMenu("Fill", f_menu);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	myinit();
	glutReshapeFunc(myReshape);					// 함수 저장 
	glutKeyboardFunc(key);
	glutMouseFunc(mymouse);						// mouse에 대한 d이벤트가 생기면 mymouse를 무조건 호출함
	glutDisplayFunc(mydisplay);					// 제일 처음으로 
	glutMainLoop();								// mydisplay 함수로 감 
	return 0;
}
