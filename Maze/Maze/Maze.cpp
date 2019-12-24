#include "Maze.h"
#include <fstream>
#include <GL/glut.h>
#include <GL/GLAUX.H>

#define GL_CLAMP_TO_EDGE 0x812F

Maze::Maze() : mazeSize(0)
{
	start = new int[3];
	end = new int[3];
	texture = _loadTexture("resources/skybox/down.bmp");
}

Maze::~Maze()
{
	glDeleteTextures(1, &texture);
}


bool Maze::loadMap(const char* _filename)
{
	char* readLine;

	ifstream in(_filename);
	if (in.fail())
	{
		return 0;
	}

	in >> mazeSize;
	
	Map.resize(mazeSize);
	for (int i = 0; i < mazeSize; i++)
	{
		Map[i].resize(mazeSize);
		for (int j = 0; j < mazeSize; j++)
		{
			Map[i][j].resize(mazeSize);
		}
	}

	readLine = new char[mazeSize + 1];
	for (int y = 0; y < mazeSize; y++)
	{
		for (int x = 0; x < mazeSize; x++)
		{
			in >> readLine;
			for (int z = 0; z < mazeSize; z++)
			{
				Map[x][y][z] = readLine[z];
				if (readLine[z] == 's')
				{
					start[0] = x;
					start[1] = y;
					start[2] = z;
				}
				else if (readLine[z] == 'e')
				{
					end[0] = x;
					end[1] = y;
					end[2] = z;
				}
			}
		}
	}
	delete[] readLine;

	return 1;
}

void Maze::drawMaze()
{
	for (int y = 0; y < mazeSize; y++)
	{
		for (int x = 0; x < mazeSize; x++)
		{
			for (int z = 0; z < mazeSize; z++)
			{
				if (Map[x][y][z] == '1') {
					glPushMatrix();
					glTranslatef(x + 0.5, y + 0.5, z + 0.5);
					glColor3f(0.66, 0.88, 0.9);
					drawBox(0.8);
					glPopMatrix();
				}
			}	
		}
	}
}

// Skybox의 draw를 가져옴
void Maze::drawBox(float size = 1.0)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//front
	glBindTexture(GL_TEXTURE_2D, texture);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-size/2, -size/2, -size/2);
	glTexCoord2f(1.0, 0.0); glVertex3f( size/2, -size/2, -size/2);
	glTexCoord2f(1.0, 1.0); glVertex3f( size/2,  size/2, -size/2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-size/2,  size/2, -size/2);
	glEnd();

	//back
	glBindTexture(GL_TEXTURE_2D, texture);
	glNormal3f(0, 0,-1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f( size/2, -size/2,  size/2);
	glTexCoord2f(1.0, 0.0); glVertex3f(-size/2, -size/2,  size/2);
	glTexCoord2f(1.0, 1.0); glVertex3f(-size/2,  size/2,  size/2);
	glTexCoord2f(0.0, 1.0); glVertex3f( size/2,  size/2,  size/2);
	glEnd();

	//left
	glBindTexture(GL_TEXTURE_2D, texture);
	glNormal3f(-1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f( size/2, -size/2, -size/2);
	glTexCoord2f(1.0, 0.0); glVertex3f( size/2, -size/2,  size/2);
	glTexCoord2f(1.0, 1.0); glVertex3f( size/2,  size/2,  size/2);
	glTexCoord2f(0.0, 1.0); glVertex3f( size/2,  size/2, -size/2);
	glEnd();

	//right
	glBindTexture(GL_TEXTURE_2D, texture);
	glNormal3f(1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-size/2, -size/2,  size/2);
	glTexCoord2f(1.0, 0.0); glVertex3f(-size/2, -size/2, -size/2);
	glTexCoord2f(1.0, 1.0); glVertex3f(-size/2,  size/2, -size/2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-size/2,  size/2,  size/2);
	glEnd();

	//up
	glBindTexture(GL_TEXTURE_2D, texture);
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-size/2,  size/2, -size/2);
	glTexCoord2f(1.0, 0.0); glVertex3f( size/2,  size/2, -size/2);
	glTexCoord2f(1.0, 1.0); glVertex3f( size/2,  size/2,  size/2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-size/2,  size/2,  size/2);
	glEnd();

	//down
	glBindTexture(GL_TEXTURE_2D, texture);
	glNormal3f(0,-1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-size/2, -size/2,  size/2);
	glTexCoord2f(1.0, 0.0); glVertex3f( size/2, -size/2,  size/2);
	glTexCoord2f(1.0, 1.0); glVertex3f( size/2, -size/2, -size/2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-size/2, -size/2, -size/2);
	glEnd();

	glPopMatrix();
}

// Skybox 클래스의 _loadTexture을 그대로 가져옴
unsigned int Maze::_loadTexture(const char* filename) {
	AUX_RGBImageRec* img = auxDIBImageLoadA(filename);
	// 텍스쳐 생성
	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->sizeX, img->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, img->data);
	// 텍스쳐 확장 보간법 선정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// CLAMP_TO_EDGE 파라메터는 EDGE의 색상으로 경계를 확장
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	// 메모리 할당 해제
	free(img->data);
	free(img);
	return texId;
}

char Maze::mazeInfo(const int* pos) const
{
	if (pos[0] >= mazeSize || pos[1] >= mazeSize || pos[2] >= mazeSize || pos[0] < 0 || pos[1] < 0 || pos[2] < 0) return -1;

	return Map[pos[0]][pos[1]][pos[2]];
}

char Maze::mazeInfo(const int x, const int y, const int z) const
{
	if (x >= mazeSize || y >= mazeSize || z >= mazeSize || x < 0 || y < 0 || z < 0) return -1;

	return Map[x][y][z];
}

int* Maze::getStartPoint() const
{
	return start;
}

int* Maze::getEndPoint() const
{
	return end;
}

int Maze::getSize() const
{
	return mazeSize;
}
