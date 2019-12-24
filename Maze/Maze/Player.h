#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Camera.h"

class Player {
public:
	// �÷��̾��� ��ġ
	GLfloat loc[3];
	// vel[0] = Forward, vel[1] = Up, vel[2] = Right
	GLfloat vel[3];
	// acc[0] = Forward, acc[1] = Up, acc[2] = Right
	GLfloat acc[3];
	// Player �̵��� dir�� x, z�ุ �̿��� ( dir[0], dir[2] )
	GLfloat dir[3];
	GLfloat right[3];
	// rot[0] = x �� ȸ�� ��, rot[1] = y �� ȸ�� ��, rot[2] = z �� ȸ�� ��
	GLfloat rot[3];
	// Player�� ũ��
	GLfloat size[3];
	bool onGround;
	// �÷��̾� ����
	Camera p_camera;

	GLint pos[3];


	Player();

	// �÷��̾� ��ġ ����
	void update();
	// ���� �浹�� üũ
	void collision(const GLfloat, const GLfloat, const GLfloat);

	// �÷��̾� �ش� ��ġ�� int�� x, y, z��ǥ�� ��ȯ ( �̷ο��� ��� ��ġ���� �Ǻ��� �� ��� )
	GLint* getPos();

	// �÷��̾��� ��ġ�� �����ϴ� ���� ( �������� ��ġ��ų �� ��� )
	void setPos(const GLint*);
	// ���콺 �̵��� ���� �÷��̾�� ī�޶��� ȸ�� ������ ����
	void setRot(const GLfloat*);
	
	// vel�� ���ӵ� ����� ���� �Լ�
	void addVel(const GLfloat, const GLfloat, const GLfloat);
	// x, y, z�� �� �ϳ��� vel���� set��.
	void setVel(const GLint, const GLfloat);
};

#endif