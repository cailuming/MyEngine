#pragma once
#include"Macro.h"
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
	char *readFile(const char *filename);
private:
	FILE *file;
};

