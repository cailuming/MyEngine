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
	unsigned short *readDataFile(const char *filename);
	int convertToUnicode(const unsigned char *src, unsigned short &des);
	void readConfigFile(const char *filename);
	void clearBuff();
 
private:
	FILE *file;
	char *tempBuff;
	unsigned short *unistr;
public:
	Config config;
};

