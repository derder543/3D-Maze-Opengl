#pragma once
#ifndef __MAZE_H__
#define __MAZE_H__
#include <vector>
using namespace std;

class Maze
{
private:
	int mazeSize;
	// 시작 지점
	int* start;
	// 끝 지점
	int* end;
	// 맵 데이터
	vector<vector<vector<char>>> Map;
	unsigned int texture;

public:

	Maze();
	~Maze();

	// filename을 입력받아 미로 맵 데이터를 입력받는 역할
	bool loadMap(const char*);

	// 미로를 그리는 역할
	void drawMaze();
	void drawBox(float);

	// x, y, z 좌표를 주면 그 지점이 어떤 곳인지 반환
	char mazeInfo(const int*) const;
	char mazeInfo(const int, const int, const int) const;
	static unsigned int _loadTexture(const char*);

	// 시작 및 끝 지점을 int형 x, y, z 좌표로 반환
	int* getStartPoint() const;
	int* getEndPoint() const;

	int getSize() const;
};

#endif
