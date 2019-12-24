#include "GL/glut.h"
#include "cmath"

#define ParticleNum 10000

typedef struct {
	float position[3];
	float oldPos[3];
	float velocity[3];
	float color[3];
	float energy;
	float size;
} Attrib_Particle;

Attrib_Particle Particle[ParticleNum];

void Draw_And_Update_Particle()
{
	for (int i = 0; i < ParticleNum; i++)
	{
		glPointSize(Particle[i].size);
		glBegin(GL_POINTS);
		glColor4f(Particle[i].color[0], Particle[i].color[1], Particle[i].color[2], Particle[i].energy);
		glVertex3f(Particle[i].position[0], Particle[i].position[1], Particle[i].position[2]);
		glEnd();
		Particle[i].position[0] = Particle[i].oldPos[0] + Particle[i].velocity[0];
		Particle[i].position[1] = Particle[i].oldPos[1] + Particle[i].velocity[1];
		Particle[i].position[2] = Particle[i].oldPos[2] + Particle[i].velocity[2];
		Particle[i].oldPos[0] = Particle[i].position[0];
		Particle[i].oldPos[1] = Particle[i].position[1];
		Particle[i].oldPos[2] = Particle[i].position[2];
		Particle[i].energy -= 0.01f;
	}
}

float br(float min, float max)
{
	return min + (rand() % 100) * (max - min) / 100;
}

void Init_Particle(const float height, const int size)
{
	for (int i = 0; i < ParticleNum; i++)
	{
		Particle[i].color[0] = 1;//br(0.0f,1.0f);
		Particle[i].color[1] = 1;//br(0.0f,1.0f);
		Particle[i].color[2] = 1;//br(0.0f,1.0f);
		Particle[i].oldPos[0] = br(-size, size);
		Particle[i].oldPos[1] = br(1.0f, height);
		Particle[i].oldPos[2] = br(-size, size);
		Particle[i].velocity[0] = br(-0.01f, 0.01f);
		Particle[i].velocity[1] = br(-0.01f, 0.01f);
		Particle[i].velocity[2] = 0.0f;

		Particle[i].position[0] = Particle[i].oldPos[0] + Particle[i].velocity[0];
		Particle[i].position[1] = Particle[i].oldPos[1] + Particle[i].velocity[1];
		Particle[i].position[2] = Particle[i].oldPos[2] + Particle[i].velocity[2];

		Particle[i].size = br(0.0f, 1.5f);
		Particle[i].energy = br(1.0f, 5.0f);
	}
}