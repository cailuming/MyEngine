#pragma once
#include"Macro.h"
#include<fttypes.h>
#include<ft2build.h>
#include<freetype\freetype.h>
#pragma comment(lib, "freetype.lib")
#include FT_FREETYPE_H
class CFontData
{
private:
	CFontData();
	~CFontData();
public:
	static CFontData *font;
	static CFontData *create();
	static void release();
private:
	FT_Library    library = NULL;
	FT_Face       face = NULL;
	FT_Error      error = NULL;
public:
	void initFontFromFile(const char *fontname);
	void initFontFromData(const unsigned char *buffer);
};

