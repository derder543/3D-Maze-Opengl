#include "Player.h"
#include "Maze.h"
#include <cstring>
#include <ctime>
#include <cmath>

clock_t Old_time, Cur_time;
extern Maze this_maze;

float getDt()
{
	GLfloat dt;

	Cur_time = clock();
	dt = static_cast<GLfloat>(Cur_time - Old_time) / CLOCKS_PER_SEC;
	Old_time = Cur_time;

	return dt;
}
Player::Player() : onGround(true)
{
	memset(loc, 0, sizeof(loc));	
	memset(vel, 0, sizeof(vel));
	memset(acc, 0, sizeof(acc));
	memset(rot, 0, sizeof(rot));
	memset(dir, 0, sizeof(dir));
	memset(right, 0, sizeof(right));
	memset(size, 0, sizeof(size));

	size[0] = size[1] = size[2] = 0.25;
	acc[1] = -9.8; // Gravity
	p_camera = Camera();
	Old_time = clock();
}

void Player::update()
{
	float dt = getDt();

	addVel(acc[0] * dt, 0, acc[2] * dt);
	if(!onGround) addVel(0, acc[1] * dt, 0);    // 지면에서 중력을 받지 않음.
	getPos();
	if(this_maze.mazeInfo(pos[0], pos[1]-1, pos[2]) == '0') onGround = false;   // 고지대에서 낙하

	loc[0] += (dir[0] * vel[0] + right[0] * vel[2]) * dt;
	collision(dir[0] * vel[0] + right[0]	* vel[2], 0, 0);
	loc[1] += vel[1] * dt;
	collision(0, vel[1], 0);
	loc[2] += (dir[2] * vel[0] + right[2] * vel[2]) * dt;
	collision(0, 0, dir[2] * vel[0] + right[2] * vel[2]);

	p_camera.setCameraLoc(loc);
	p_camera.applyLens();
	p_camera.applyCamera();
}

// 출처 : https://www.youtube.com/watch?v=6RxIeguVLcM&t=595s	
void Player::collision(const GLfloat dx, const GLfloat dy, const GLfloat dz)
{
	float start[3], end[3];
	for (int i = 0; i < 3; i++)
	{
		start[i] = loc[i] - size[i];
		end[i] = loc[i] + size[i];
	}
	for (int x = start[0]; x < end[0]; x++)
		for (int y = start[1]; y < end[1]; y++)
			for (int z = start[2]; z < end[2]; z++) {
				if (this_maze.mazeInfo(x, y, z) == '1')
				{
					if (dx > 0) loc[0] = x - size[0];
					else if (dx < 0) loc[0] = x + size[0] + 1;
					if (dy > 0) { loc[1] = y - size[1]; vel[1] = 0; }
					else if (dy < 0) { loc[1] = y + size[1] + 1; vel[1] = 0;  onGround = true; }
					if (dz > 0) loc[2] = z - size[2];
					else if (dz < 0) loc[2] = z + size[2] + 1;
				}
			}
}

// 플레이어의 현재 좌표를 얻는 함수
int* Player::getPos()
{
	pos[0] = static_cast<GLint>(loc[0]);
	pos[1] = static_cast<GLint>(loc[1]);
	pos[2] = static_cast<GLint>(loc[2]);

	return pos;
}

void Player::setPos(const GLint *_loc)
{
	for (int i = 0; i < 3; i+=2)
	{
		loc[i] = static_cast<GLfloat>(_loc[i]) + 0.5;
	}
	loc[1] = static_cast<GLfloat>(_loc[1]) + 0.5 + size[1];
	p_camera.setCameraLoc(loc);
}

void Player::setRot(const GLfloat *_rot)
{
	p_camera.setRot(_rot);
	p_camera.rotateCamera();
	memcpy(rot, _rot, sizeof(rot));

	memcpy(dir, rotate(init_dir, rot[1], ROTATION_YAW), sizeof(dir));
	memcpy(right, rotate(init_right, rot[1], ROTATION_YAW), sizeof(right));
}

void Player::addVel(const GLfloat _vx, const GLfloat _vy, const GLfloat _vz)
{
	vel[0] += _vx;
	vel[1] += _vy;
	vel[2] += _vz;

	// 최대 속도 제한
	for (int i = 0; i < 3; i+=2)
	{
		if (vel[i] >  1) vel[i] =  1;
		if (vel[i] < -1) vel[i] = -1;
	}
}

void Player::setVel(const GLint _type, const GLfloat _v)
{
	vel[_type] = _v;
}


