#pragma once
#include"Macro.h"
#include<ft2build.h>
#include"CTexture.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CConstBuffer.h"
#include "CShaders.h"
#include "CFileReader.h"

#pragma comment(lib, "freetype.lib")
#include FT_FREETYPE_H
#include FT_GLYPH_H
 
struct Glyph {
	int width;
	int height;
	int advance;
	int bit_top;
	int bit_left;
	int pitch;
 
	unsigned char *buff;
	~Glyph() {
		delete buff;
		buff = 0;
	}
};

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
	CTexture *fontTexture;
	FT_GlyphSlot slot;
	Glyph *data;
public:
	int textureWidth;
	int textureHeight;
	int charNumPerRow;
	int charNumPerCol;
	int fontSize;
public:
	CVertexBuffer vBuffer;
	CIndexBuffer iBuffer;
	CConstBuffer cBuffer;
	GBuffer gbuffer;
	CShaders *shader;
private:
	void drawFontToBuffer(int x, int y, unsigned char *&buff, Glyph &data);
public:
	void initFontFromFile(const char *fontname);
	void setFontInfo(int width,int height,int fontSize);
	void genFontTexture(const unsigned short *str);
public:
	void InitBuffer();
	void onCompileShader(const char *shadercode);
	void updateGBuffer(D3DXMATRIX mat, float iTime, float width, float height);
	void render();
};

