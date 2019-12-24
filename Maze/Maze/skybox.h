#ifndef __SKYBOX_H__
#define __SKYBOX_H__

// Open Source

class Skybox {
public:
	Skybox();
	~Skybox();
	void draw();

private:
	typedef unsigned int uint;
	typedef const char * pcStr;
	uint textures[6];
	static uint _loadTexture(pcStr filename);
};

#endif