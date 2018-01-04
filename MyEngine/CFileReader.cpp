#include "CFileReader.h"

CFileReader::CFileReader()
{
}

CFileReader::~CFileReader()
{
}

CFileReader *CFileReader::reader = 0;

CFileReader *CFileReader::create() {
	if (!reader) {
		reader = new CFileReader();
	}
	return reader;
};
void CFileReader::destroy() {
	if (reader) {
		delete reader;
		reader = 0;
	}
};

char *CFileReader::readFile(const char *filename) {
	errno_t err = fopen_s(&file, filename, "r");
	char *buff =0;
	if (file) {
		fseek(file, 0, 2);
		int filelen = ftell(file);
		fseek(file, 0, 0);
		buff = new char[filelen];
		memset(buff, 0, sizeof(char)*filelen);
		filelen=fread_s(buff, filelen, 1,filelen, file);
		fflush(file);
		fclose(file);
	}
	else {
		::OutputDebugString((char*)err);
	}

	return buff;

};

