#include "Camera.h"
#include <cstring>
#include <cmath>

float* rotate(const GLfloat* _v, const GLfloat _angle, const GLfloat* _axis)
{
	const GLfloat c = cos(_angle), s = sin(_angle), C = 1 - c;
	const GLfloat x = _axis[0], y = _axis[1], z = _axis[2];
	GLfloat ret[3];
	GLfloat R[3][3] = { x*x*C + c, x*y*C - z * s, x*z*C + y * s, y*x*C + z * s, y*y*C + c, y*z*C - x * s, z*x*C - y * s, z*y*C + x * s, z*z*C + c };

	for (int i = 0; i < 3; i++)
	{
		ret[i] = 0;
		for (int j = 0; j < 3; j++)
		{
			ret[i] += _v[j] * R[i][j];
		}
	}

	return ret;
}

Camera::Camera() : asp(1.0), fov(60.0), near(0.1), far(100.0)
{
	memset(loc, 0.0, sizeof(loc));
	memset(tar, 0.0, sizeof(tar));
	memset(up, 0.0, sizeof(up));
	memset(right, 0.0, sizeof(right));
	memset(rot, 0.0, sizeof(rot));
	memset(dir, 0.0, sizeof(dir));

	up[1] = 1.0;
	right[0] = tar[2] = dir[2] = -1.0;
}

void Camera::setCameraLoc(const GLfloat* _loc)
{
	memcpy(loc, _loc, sizeof(loc));
	setTarget();
}

void Camera::setRot(const GLfloat *_rot)
{
	memcpy(rot, _rot, sizeof(rot));
}

void Camera::setTarget()
{
	for (int i = 0; i < 3; i++)
	{
		tar[i] = loc[i] + dir[i];
	}
}

void Camera::applyCamera() const
{
	gluLookAt(loc[0], loc[1], loc[2], tar[0], tar[1], tar[2], up[0],  up[1],  up[2]);
}

void Camera::applyLens() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, asp, near, far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::rotateCamera()
{
	memcpy(dir, rotate(init_dir, rot[0], ROTATION_PITCH), sizeof(dir));
	memcpy(up, rotate(init_up, rot[0], ROTATION_PITCH), sizeof(up));
	memcpy(right, rotate(init_right, rot[0], ROTATION_PITCH), sizeof(right));
	memcpy(dir, rotate(dir, rot[1], ROTATION_YAW), sizeof(dir));
	memcpy(up, rotate(up, rot[1], ROTATION_YAW), sizeof(up));
	memcpy(right, rotate(init_right, rot[1], ROTATION_YAW), sizeof(right));
	setTarget();
}