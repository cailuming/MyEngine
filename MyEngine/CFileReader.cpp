#include "CFileReader.h"

CFileReader::CFileReader()
{
	memset(this, 0, sizeof(*this));
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
 
char *CFileReader::readShaderFile(const char *filename) {
	if (filename) {
		errno_t err = fopen_s(&file, filename, "r");
	}
	else {
		errno_t err = fopen_s(&file, config.curShaderName, "r");
	}
	clearBuff();
	if (file) {
		fseek(file, 0, 2);
		int filelen = ftell(file);
		fseek(file, 0, 0);
		tempBuff = new char[filelen];
		memset(tempBuff, 0, sizeof(char)*filelen);
		filelen = fread_s(tempBuff, filelen, 1, filelen, file);
		fflush(file);
		fclose(file);
	}
	else {
		 
		MessageBox(0, "Failed to open the file!", 0, 0);
	}

	return tempBuff;
};
 

void CFileReader::readConfigFile(const char *filename) {
	errno_t err = fopen_s(&file, filename, "r");
	 
	if (file) {
		 
		fscanf_s(file, "screen_width: %d\n", &config.screenWidth);
		fscanf_s(file, "screen_height: %d\n", &config.screenHeight);
		fscanf_s(file, "current_ps_shader_file_name: %s \n", config.curShaderName,256);

		fflush(file);
		fclose(file);
	}
	else {
		::OutputDebugString((char*)err);
		MessageBox(0, "Failed to open the file!", 0, 0);
	}
};


void CFileReader::clearBuff() {
	if (tempBuff) {
		delete tempBuff;
		tempBuff = 0;
	}
};

