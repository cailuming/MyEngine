#pragma once
#include"Macro.h"

struct Config {
	int screenWidth;
	int screenHeight;
	char curShaderName[256];
};

class CFileReader
{
private:
	CFileReader();
	~CFileReader();
public:
	static CFileReader *reader;
	static CFileReader *create();
	static void destroy();
public:
	char *readShaderFile(const char *filename);
	char *readInternalShaderFile(const char *filename);
	void readConfigFile(const char *filename);
	void clearBuff();
private:
	FILE *file;
	char *tempBuff;
public:
	Config config;
};

