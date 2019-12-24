#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <GL/glut.h>

float* rotate(const GLfloat*, const GLfloat, const GLfloat*);

// Rotation ��
const GLfloat ROTATION_YAW[3] = { 0.0, 1.0, 0.0 };
const GLfloat ROTATION_PITCH[3] = { 1.0, 0.0, 0.0 };

// �ʱ� Dir, Up �� ( �ʱ� ���� �� �� ȸ�� ���� ����ؼ� dir, up�� ���� )
const GLfloat init_dir[3] = { 0, 0, -1.0 };
const GLfloat init_up[3] = { 0, 1.0, 0 };
const GLfloat init_right[3] = {-1.0, 0, 0 };

// Camera Ŭ������ �÷��̾��� ������ ǥ���ϴ� �͸����� ����Ǿ� ����

class Camera {
public:
	GLfloat loc[3];
	GLfloat tar[3];
	GLfloat up[3];
	GLfloat right[3];
	// rot[0] = x �� ȸ�� ��, rot[1] = y �� ȸ�� ��, rot[2] = z �� ȸ�� ��
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

	// rot�� �̿��� ī�޶� ȸ��
	void rotateCamera();
};
#endif