#include "CFontData.h"

CFontData::CFontData()
{
	memset(this, 0, sizeof(*this));
	
}

CFontData::~CFontData()
{
}

CFontData * CFontData::font=0;

CFontData *CFontData::create() {
	if (nullptr==font) {
		font = new CFontData();
	}
	return font;
};

void CFontData::release() {
	if (font) {
		delete font;
		font = 0;
	}
};
 
void CFontData::initFontFromData(const unsigned char *buffer) {
	error = FT_Init_FreeType(&library);
	if (error)
	{
		library = 0;
		printf(" There is some error when Init Library ");
	}
	 
	error = FT_New_Memory_Face(library,
		
		buffer,    /* first byte in memory */
		strlen((char*)buffer),      /* size in bytes        */
		0,         /* face_index           */
		&face);
	if (error == FT_Err_Unknown_File_Format)
	{
		::OutputDebugString("File format is not supported");
	}
	else if (error)
	{
		::OutputDebugString("Unknown error!");
	}

};

void CFontData::initFontFromFile(const char *fontname) {
	error = FT_Init_FreeType(&library);
	if (error)
	{
		library = 0;
		printf(" There is some error when Init Library ");

	}
	error = FT_New_Face(library,
		fontname,
		0,
		&face);
	if (error == FT_Err_Unknown_File_Format)
	{
		::OutputDebugString("File format is not supported");
	}
	else if (error)
	{
		::OutputDebugString("Unknown error!");
	}
};
