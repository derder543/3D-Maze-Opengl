#pragma once
#ifndef __MAZE_H__
#define __MAZE_H__
#include <vector>
using namespace std;

class Maze
{
private:
	int mazeSize;
	// ���� ����
	int* start;
	// �� ����
	int* end;
	// �� ������
	vector<vector<vector<char>>> Map;
	unsigned int texture;

public:

	Maze();
	~Maze();

	// filename�� �Է¹޾� �̷� �� �����͸� �Է¹޴� ����
	bool loadMap(const char*);

	// �̷θ� �׸��� ����
	void drawMaze();
	void drawBox(float);

	// x, y, z ��ǥ�� �ָ� �� ������ � ������ ��ȯ
	char mazeInfo(const int*) const;
	char mazeInfo(const int, const int, const int) const;
	static unsigned int _loadTexture(const char*);

	// ���� �� �� ������ int�� x, y, z ��ǥ�� ��ȯ
	int* getStartPoint() const;
	int* getEndPoint() const;

	int getSize() const;
};

#endif
