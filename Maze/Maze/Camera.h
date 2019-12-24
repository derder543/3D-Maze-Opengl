#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <GL/glut.h>

float* rotate(const GLfloat*, const GLfloat, const GLfloat*);

// Rotation 축
const GLfloat ROTATION_YAW[3] = { 0.0, 1.0, 0.0 };
const GLfloat ROTATION_PITCH[3] = { 1.0, 0.0, 0.0 };

// 초기 Dir, Up 값 ( 초기 값과 각 축 회전 각을 사용해서 dir, up을 구함 )
const GLfloat init_dir[3] = { 0, 0, -1.0 };
const GLfloat init_up[3] = { 0, 1.0, 0 };
const GLfloat init_right[3] = {-1.0, 0, 0 };

// Camera 클래스는 플레이어의 시점을 표현하는 것만으로 설계되어 있음

class Camera {
public:
	GLfloat loc[3];
	GLfloat tar[3];
	GLfloat up[3];
	GLfloat right[3];
	// rot[0] = x 축 회전 각, rot[1] = y 축 회전 각, rot[2] = z 축 회전 각
	GLfloat rot[3];
	GLfloat dir[3];
	GLfloat asp;
	GLfloat fov;
	GLfloat near;
	GLfloat far;

	Camera();
	void setCameraLoc(const GLfloat*);
	void setRot(const GLfloat*);
	void setTarget();

	void applyCamera() const;
	void applyLens() const;

	// rot을 이용해 카메라 회전
	void rotateCamera();
};
#endif