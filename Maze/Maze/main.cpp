#include "Particle.cpp"
#include <iostream>
#include "Player.h"
#include "Skybox.h"
#include "Maze.h"
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

#define TEXT_FONT   GLUT_BITMAP_8_BY_13

GLint Window_Width = 800, Window_Height = 600;
GLint Window_Position_X = 0, Window_Position_Y = 0;

GLdouble Center_X = Window_Width / 2, Center_Y = Window_Height / 2;
GLfloat spin = 0.0;

int *P_pos = NULL, *end_pos = NULL;
bool playable = true, charging = false;

const float height = 15.0;

const char* filename[3] = {"map_easy.txt", "map_hard.txt", NULL};
int level = 0;

// rot[0] = x축 회전 각, rot[1] = y축 회전 각, rot[2] = z축 회전 각
GLfloat rot[3] = { 0.0, 0.0, 0.0 };
const GLfloat Ld[4] = { 1.0, 1.0, 1.0, 1.0 }, Ls[4] = { 1.0, 1.0, 1.0, 1.0 }, La[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat Md[4] = { 1.0, 1.0, 1.0, 1.0 }, Ms[4] = { 1.0, 1.0, 1.0, 1.0 }, Ma[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat shine[1] = { 50.0 };
const GLfloat Lpos[3][4] = { { 5.0, 20.0, 5.0, 0.0 }, { -5.0, -5.0, -5.0, 0.0 }, { 15.0, -5.0, 15.0, 0.0 } };

Maze this_maze;
Player myPlayer;
Skybox* skybox;

clock_t space_p, space_r;

// bitmap 출력(화면에 글자 표시)
// 출처 : https://www.opengl.org/archives/resources/features/fontsurvey/#glut
void printString(const char* s)
{
	while (*s) {
		glutBitmapCharacter(TEXT_FONT, *s);
		s++;
	}
}

void printString(string s)
{
	int i = 0;
	while (s[i]) {
		glutBitmapCharacter(TEXT_FONT, s[i]);
		i++;
	}
}

void printString(int s)
{
	glutBitmapCharacter(TEXT_FONT, s);
}

void textDisplay() 
{
	glPushMatrix();
	glColor3f(1, 0, 0);

	// player Pos
	glRasterPos3f(myPlayer.p_camera.loc[0] + myPlayer.p_camera.dir[0] + myPlayer.p_camera.right[0] * 0.55 + myPlayer.p_camera.up[0] * 0.5,
		myPlayer.p_camera.loc[1] + myPlayer.p_camera.dir[1] + myPlayer.p_camera.right[1] * 0.55 + myPlayer.p_camera.up[1] * 0.5,
		myPlayer.p_camera.loc[2] + myPlayer.p_camera.dir[2] + myPlayer.p_camera.right[2] * 0.55 + myPlayer.p_camera.up[2] * 0.5);
	printString("Real Pos : ");
	printString(to_string(myPlayer.loc[0]));
	printString(", ");
	printString(to_string(myPlayer.loc[1]));
	printString(", ");
	printString(to_string(myPlayer.loc[2]));

	printString(" / Player Pos : ");
	printString(to_string(P_pos[0]));
	printString(", ");
	printString(to_string(P_pos[1]));
	printString(", ");
	printString(to_string(P_pos[2]));

	printString(" / Maze Info : ");
	printString(this_maze.mazeInfo(P_pos));
	glPopMatrix();
}

// 두 x, y, z 좌표가 일치하는지 체크하기위한 함수
bool equal(int* a, int *b)
{
	return (a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]);
}

void pressKey(const unsigned char key, const GLint x, const GLint y)
{
	if (key == 'w')
	{
		myPlayer.vel[0] = 1.0;
	}
	if (key == 'a')
	{
		myPlayer.vel[2] = 1.0;
	}
	if (key == 's')
	{
		myPlayer.vel[0] = -1.0;
	}
	if (key == 'd')
		{
		myPlayer.vel[2] = -1.0;
	}
	if (key == ' ' && myPlayer.onGround)   // space bar
	{
		space_p = clock();
		charging = true;
	}
	if (key == 27)    // esc : end game
	{
		exit(0);
	}
}

void releaseKey(const unsigned char key, const int x, const int y)
{
	if (key == 'w' || key == 's')
	{
		myPlayer.vel[0] = 0.0;
	}
	if (key == 'a' || key == 'd')
	{
		myPlayer.vel[2] = 0.0;
	}
	if (key == ' ' && charging)   // space bar
	{		
		space_r = clock();
		float power = static_cast<GLfloat>(space_r - space_p) / CLOCKS_PER_SEC;
		if (power < 0.3)
			myPlayer.vel[1] = 5.0;
		else
			myPlayer.vel[1] = 5.0 + power * 4.0;
		myPlayer.onGround = false;
		charging = false;
	}
}

void MouseMove(const int x, const int y)
{
	rot[0] += (Center_Y - y) / 200.0;
	rot[1] += (Center_X - x) / 200.0;

	// 위 아래 최대 각 제어
	if (rot[0] >= 1.5f) rot[0] = 1.5f;
	if (rot[0] <= -1.5f) rot[0] = -1.5f;
	myPlayer.setRot(rot);
}

void drawEndPoint()
{
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(static_cast<GLfloat>(end_pos[0]) + 0.5, static_cast<GLfloat>(end_pos[1]) + 0.5, static_cast<GLfloat>(end_pos[2]) + 0.5);
	glRotatef(spin, 1, 1, 0);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
}

void drawScene()
{
	skybox->draw();
	this_maze.drawMaze();
	textDisplay();
	Draw_And_Update_Particle();
	drawEndPoint();
}

void MapLoading(const int n)
{
	// 맵 파일 로딩
	if (!this_maze.loadMap(filename[n]))
	{
		cout << "Error: Cannot read File." << endl;
		exit(-1);
	}
	// 플레이어 시작지점 설정
	myPlayer.setPos(this_maze.getStartPoint());
	end_pos = this_maze.getEndPoint();
	Init_Particle(height, this_maze.getSize());
}


void MazeControl()
{
	if (playable) {
		spin += 1;
		P_pos = myPlayer.getPos();
		// reset buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glutWarpPointer(Center_X, Center_Y);

		if (equal(P_pos, end_pos))
		{
			level++;
			if (filename[level] == NULL)
			{
				glColor3f(1, 0, 0);
				glRasterPos3f(myPlayer.p_camera.loc[0] + myPlayer.p_camera.dir[0] * 0.1, myPlayer.p_camera.loc[1] + myPlayer.p_camera.dir[1] * 0.1, myPlayer.p_camera.loc[2] + myPlayer.p_camera.dir[2] * 0.1);
				printString("Congratuation!! You Escaped!! (Press \"Esc\" to end.)");
				playable = false;
			}
			else
			{
				MapLoading(level);
			}
		}

		myPlayer.update();
		drawScene();

		glFlush();
	}
}

// Opengl 관련 Initialize
void glInit()
{
	glClearColor(0, 0.0, 0.0, 0);
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Ld);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Ls);
	glLightfv(GL_LIGHT0, GL_AMBIENT, La);
	glLightfv(GL_LIGHT0, GL_POSITION, Lpos[0]);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Ld);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Ls);
	glLightfv(GL_LIGHT1, GL_AMBIENT, La);
	glLightfv(GL_LIGHT1, GL_POSITION, Lpos[1]);
	
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Ld);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Ls);
	glLightfv(GL_LIGHT2, GL_AMBIENT, La);
	glLightfv(GL_LIGHT2, GL_POSITION, Lpos[2]);

	glMaterialfv(GL_FRONT, GL_SPECULAR, Ms);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ma);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

// 그 외 Initialize
void Init()
{
	skybox = new Skybox();
}

int main(int argc, char **argv)
{
	
	// Window 생성
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(Window_Width, Window_Height);
	glutInitWindowPosition(Window_Position_X, Window_Position_Y);
	glutCreateWindow("Maze");

	MapLoading(0);
	glInit();
	Init();

	glutDisplayFunc(MazeControl);
	glutIdleFunc(MazeControl);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(releaseKey);	
	glutPassiveMotionFunc(MouseMove);

	glutMainLoop();
	return 0;
}