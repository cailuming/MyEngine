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
		errno_t err = fopen_s(&file, filename, "rb");
	}
	else {
		errno_t err = fopen_s(&file, config.curShaderName, "rb");
	}
	clearBuff();
	if (file) {
		fseek(file, 0, 2);
		int filelen = ftell(file);
		fseek(file, 0, 0);
		tempBuff = new char[filelen+1];
		memset(tempBuff, 0, sizeof(char)*(filelen+1));
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


unsigned short *CFileReader::readDataFile(const char *filename) {
	if (filename) {
		errno_t err = fopen_s(&file, filename, "rb");
	}
	else {
		errno_t err = fopen_s(&file, config.curShaderName, "rb");
	}
	clearBuff();
	if (file) {
		fseek(file, 0, 2);
		int filelen = ftell(file);
		fseek(file, 0, 0);
		tempBuff = new char[filelen + 1];
		memset(tempBuff, 0, sizeof(char)*(filelen + 1));
		filelen = fread_s(tempBuff, filelen, 1, filelen, file);

		fflush(file);
		fclose(file);
	}
	else {

		MessageBox(0, "Failed to open the file!", 0, 0);
	}

	unistr = new unsigned short[1024];
	memset(unistr, 0, sizeof(unsigned short) * 1024);

	int stride = 0;
	for (int i = 0; i < strlen(tempBuff);) {
		i += convertToUnicode((unsigned char*)&tempBuff[i], unistr[stride++]);
	} 
	
	return  unistr;
};

int CFileReader::convertToUnicode(const unsigned char *src, unsigned short &des) {
	if (!src || (*src) == 0) return  0;

	unsigned char b = *(src++);

	if (b < 0x80)
	{
		des = b;
		return 1;
	}

	if (b < 0xC0 || b > 0xFD) return 0; // the src is invalid  

	size_t len;

	if (b < 0xE0)
	{
		des = b & 0x1F;
		len = 2;
	}
	else
		if (b < 0xF0)
		{
			des = b & 0x0F;
			len = 3;
		}
		else
			if (b < 0xF8)
			{
				des = b & 0x07;
				len = 4;
			}
			else
				if (b < 0xFC)
				{
					des = b & 0x03;
					len = 5;
				}
				else
				{
					des = b & 0x01;
					len = 6;
				}

	size_t i = 1;
	for (; i < len; ++i)
	{
		b = *(src++);
		if (b < 0x80 || b > 0xBF) return 0; // the src is invalid  
		des = (des << 6) + (b & 0x3F);
	}
	return len;
}
 
 
void CFileReader::clearBuff() {
	if (tempBuff) {
		delete tempBuff;
		tempBuff = 0;
	}

	if (unistr) {
		delete unistr;
		tempBuff=0;
	}
};

