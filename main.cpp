/*
 * GateWay
 *
 * Written by sundy 28/5/2016
 *
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <cstdio>

#include <stdlib.h>
#include <tchar.h>
#include <string>
#include "Serial/inc/SerialClass.h"
#include "GUI/inc/Interface.h"

int width = 650;
int height = 650;

void SerialTest(int com_id){
    printf("Welcome to the serial test app!\n\n");

    char comm[64];
    sprintf(comm, "\\\\.\\COM%d", com_id);
	Serial* SP = new Serial(comm);    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[2048] = "";			// don't forget to pre-allocate memory
//	printf("%s\n",incomingData);
	int dataLength = 256;
	int readResult = 0;
	int i = 0;

	while(SP->IsConnected())
	while(SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData,dataLength);
//      printf("Bytes read: (0 means no data available) %i\n",readResult);
        incomingData[readResult] = 0;

        printf("size:%d->data: ",readResult);
        if(readResult)
		{
			for(i = 0; i < readResult; i++)
			{
				printf("0x%X ",incomingData[i]);
			}

			printf("\n");
		}

        printf("\n");
/*size:33->data: 0x7E 0x45 0xFFFFFFA1 0x1C 0x1 0x0 0x0 0x0 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0x71 0x3D 0xFFFFFF8A 0x3E 0xFFFFFFFA 0xFFFFFFBF 0xFFFFFFA4 0x42 0x1 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0xFFFFFF93*/
		Sleep(200);
	}
}


PackagesManager* pkgs = new PackagesManager();

struct Vec2 {
	double x, y;
	Vec2(double _x=0, double _y=0) : x(_x), y(_y) {}
	Vec2 operator + (Vec2 o) { return Vec2(x+o.x, y+o.y); }
	Vec2 operator - (Vec2 o) { return Vec2(x-o.x, y-o.y); }
};

static double p_w_per = 0.8, p_h_per = 0.8;
static double p_l_screen = -1, p_r_screen = p_w_per*2-1, p_d_screen = 1-2*p_h_per, p_u_screen = 1;
static double p_l = -2, p_r = 2, p_d = -2, p_u = 2;
struct Vec2Transformer {
    static Vec2 from_platform_to_screen(Vec2 src) {
        Vec2 ret;
        ret.x = (src.x - p_l) / (p_r - p_l) * (p_r_screen - p_l_screen) + p_l_screen;
        ret.y = (src.y - p_d) / (p_u - p_d) * (p_u_screen - p_d_screen) + p_d_screen;
        return ret;
    }
};

struct Robot {
    double x, y, r, dir;
    Robot(double _x=0, double _y=0, double _r=0, double _d=0):x(_x), y(_y), r(_r), dir(_d){}
    Vec2 getO() { return Vec2(x,y); }
};

Robot r[10] = {Robot(-1,-1,0.2,0.0), Robot(0,0,0.2,PI/2), Robot(1,0,0.2, PI), Robot(1.5,1.5,0.2, PI*1.5)};

void draw(Robot &rb) {
	glColor3ub(107, 255, 107);
    glBegin(GL_POLYGON);
	for (int i = 0; i < CN; ++ i) {
		Vec2 p = Vec2Transformer::from_platform_to_screen( Vec2(rb.x+rb.r*cos(2*PI/CN*i), rb.y+rb.r*sin(2*PI/CN*i)) );
		glVertex2f(p.x, p.y);
	}
	glEnd();
	glPointSize(5);
	glColor3ub(255, 107, 107);
	glBegin(GL_POINTS);
	Vec2 p = Vec2Transformer::from_platform_to_screen( Vec2(rb.x+rb.r*0.75*cos(rb.dir), rb.y+rb.r*0.75*sin(rb.dir)) );
	glVertex2f(p.x,p.y);
	glEnd();
}


void gl_printf(void *font, char *s) {
	for (char *p = s; *p; p++)
		glutBitmapCharacter(font, *p);
}
void display_info(double x, double y, char *s) {
    glLoadIdentity();
    glColor3ub(107, 107, 255);
    glRasterPos2f(x, y);
    gl_printf(GLUT_BITMAP_HELVETICA_12, s);
}

int id = 1;
void init_screen() {
    glLoadIdentity();
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_POLYGON);
    glVertex2f(p_l_screen, p_u_screen);
    glVertex2f(p_r_screen, p_u_screen);
    glVertex2f(p_r_screen, p_d_screen);
    glVertex2f(p_l_screen, p_d_screen);
    glEnd();

    glLoadIdentity();
    glColor3f(0.9f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(p_r_screen, 1);
    glVertex2f(1, 1);
    glVertex2f(1, p_d_screen);
    glVertex2f(p_r_screen, p_d_screen);
    glEnd();

    glLoadIdentity();
    glColor3f(1.0f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -1);
    glVertex2f(-1, p_d_screen);
    glVertex2f(1, p_d_screen);
    glVertex2f(1, -1);
    glEnd();
}

void display(void) {
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	init_screen();

	glLoadIdentity();
    for (int i = 0; i < NROBOT; ++ i) {
        draw(r[i]);
    }
    double ry = 0.99, rdelta = 0.04;
    char pinfo[512];
    for (int i = 0; i < NROBOT; ++ i) {
        ry -= rdelta;
        sprintf(pinfo, "Robot %d", i+1);
        display_info(p_r_screen + 0.01, ry, pinfo);
        ry -= rdelta;
        sprintf(pinfo, "Pos: (%.2lf %.2lf)", r[i].x, r[i].y);
        display_info(p_r_screen + 0.01, ry, pinfo);
        ry -= rdelta;
        sprintf(pinfo, "Dir: %.2lf", r[i].dir);
        display_info(p_r_screen + 0.01, ry, pinfo);
    }

    double dy = -0.97, ddelta = 0.04;
    for (int iter = pkgs->rail; iter != pkgs->head; iter = pkgs->prev(iter)) {
        if (dy < p_d_screen - ddelta) {
            display_info(-0.97, dy, pkgs->data[iter]);
        } else {
            break;
        }
        dy += ddelta;
    }

	glutSwapBuffers();
	glutPostRedisplay();
	sprintf(pinfo, "This is package number %d!", id ++);
	pkgs->push(pinfo, 40);
	for (int i = 0; i < NROBOT; ++ i) {
        int rn = rand();
        if (rn % 50 == 0) {
            r[i].x += 0.01;
            r[i].y += 0.01;
        } else if (rn % 50 == 1) {
            r[i].x -= 0.01;
            r[i].y -= 0.01;
        } else if (rn % 50 == 2) {
            r[i].dir += 0.1;
        } else if (rn % 50 == 3) {
            r[i].dir -= 0.1;
        }
	}
}

void reshape(int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glOrtho(-w, w, -h, h, -1, 1);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Gateway");

//    SerialTest(3); //3 is COM3
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
    return EXIT_SUCCESS;
}
