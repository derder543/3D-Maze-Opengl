#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Camera.h"

class Player {
public:
	// 플레이어의 위치
	GLfloat loc[3];
	// vel[0] = Forward, vel[1] = Up, vel[2] = Right
	GLfloat vel[3];
	// acc[0] = Forward, acc[1] = Up, acc[2] = Right
	GLfloat acc[3];
	// Player 이동은 dir의 x, z축만 이용함 ( dir[0], dir[2] )
	GLfloat dir[3];
	GLfloat right[3];
	// rot[0] = x 축 회전 각, rot[1] = y 축 회전 각, rot[2] = z 축 회전 각
	GLfloat rot[3];
	// Player의 크기
	GLfloat size[3];
	bool onGround;
	// 플레이어 시점
	Camera p_camera;

	GLint pos[3];


	Player();

	// 플레이어 위치 갱신
	void update();
	// 벽과 충돌을 체크
	void collision(const GLfloat, const GLfloat, const GLfloat);

	// 플레이어 해당 위치를 int형 x, y, z좌표로 반환 ( 미로에서 어느 위치인지 판별할 때 사용 )
	GLint* getPos();

	// 플레이어의 위치를 변경하는 역할 ( 시작점에 위치시킬 때 사용 )
	void setPos(const GLint*);
	// 마우스 이동에 따라 플레이어와 카메라의 회전 각도를 설정
	void setRot(const GLfloat*);
	
	// vel에 가속도 계산을 위한 함수
	void addVel(const GLfloat, const GLfloat, const GLfloat);
	// x, y, z축 중 하나의 vel값을 set함.
	void setVel(const GLint, const GLfloat);
};

#endif