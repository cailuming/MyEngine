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
		::OutputDebugStringA("File format is not supported");
	}
	else if (error)
	{
		::OutputDebugStringA("Unknown error!");
	}
	setFontInfo(1280,720,20);
	InitBuffer();
};

//set the font info
void CFontData::setFontInfo(int width, int height, int size) {
	textureWidth = width;
	textureHeight = height;

	charNumPerRow = textureWidth/size;
	charNumPerCol = textureHeight / size;
	fontSize      = size;
	FT_Set_Pixel_Sizes(face, 0, size);
	 
};

// draw one character
void CFontData::drawFontToBuffer(int x, int y, unsigned char *&buff, Glyph &data) {
	for (int i = 0; i < data.height;i++) {
		memcpy(&buff[x +data.bit_left+(i+y+fontSize-data.bit_top)*textureWidth], &data.buff[i*data.width], data.width);
	}
};

void CFontData::genFontTexture(const unsigned short *str) {
	 
	int textLen = lstrlenW((wchar_t*)str);
	 
	data = new Glyph[textLen];
	 
	//copy and record the buff data
 	for (int i = 0; i <textLen;i++) {
		int glyph_index = FT_Get_Char_Index(face,str[i]);
		
		error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		
		slot = face->glyph;
	 
		data[i].width = slot->bitmap.width;
		data[i].height = slot->bitmap.rows;
		data[i].bit_left = slot->bitmap_left;
		data[i].bit_top = slot->bitmap_top;
		// why slot should shift left 6 bits,cause of 1 point equals 64 pixels 
		data[i].advance = slot->advance.x>>6;
		data[i].buff = new unsigned char[slot->bitmap.pitch*slot->bitmap.rows];
		memcpy(data[i].buff, slot->bitmap.buffer, slot->bitmap.pitch*slot->bitmap.rows);
	}
	// this glapy is single used 
	 
	int offX = 0;
	int offY = 0;
 
	unsigned char *buff = new unsigned char[textureWidth *textureHeight];
	memset(buff, 0, sizeof(unsigned char)*(textureWidth *textureHeight));
	//draw the charater to backBuffer
	 
	for (int i = 0; i < textLen;i++) {
		drawFontToBuffer(offX,offY,buff, data[i]);
		offX += data[i].advance;
		if (offX+fontSize>textureWidth) {
			offX = 0;
			offY += fontSize;
		}
	}
	
	for (int i = 0; i < fontSize;i++) {
		for (int j = 0; j < textureWidth;j++) {
			if (buff[i*textureWidth +j]) {
				::OutputDebugString("бя");
			}
			else {
				::OutputDebugString("  ");
			}
		}
		::OutputDebugString("\n");
	}

	fontTexture = new CTexture();
	fontTexture->createShaderTexture2D(textureWidth, textureHeight, buff);

	FT_Done_Face(face);
}

void CFontData::InitBuffer() {
	float size = 1;
	vertex v[] = { { -size, -size, 0, 0, 0, 1, 0, 0 },{ -size,size, 0, 0, 0, 1, 0, 1 },{ size, size, 0, 0, 0, 1, 1, 1 },{ size, -size, 0, 0, 1, 1, 1, 0 } };
	WORD indexs[] = { 0,1,2,0,2,3 };
	vBuffer.createBuffer(sizeof(v), D3D11_USAGE_DEFAULT, v);
	iBuffer.createBuffer(6 * sizeof(WORD), D3D11_USAGE_DEFAULT, indexs);
	cBuffer.createBuffer(&gbuffer, sizeof(gbuffer));
	shader = new CShaders();
}

void CFontData::onCompileShader(const char *shadercode) {

	shader->createInternalVertexShader();
	shader->createPixelShaderFromFile(shadercode, "main");
}

void CFontData::updateGBuffer(D3DXMATRIX mat, float iTime, float width, float height) {
	gbuffer.iTime = iTime;
	gbuffer.mat = mat;
	gbuffer.width = width;
	gbuffer.height = height;

	cBuffer.updateBuffer(&gbuffer, sizeof(gbuffer));
}

void CFontData::render() {
	UINT stride = sizeof(vertex);
	UINT offset = 0;
	pGContext->IASetInputLayout(shader->pLayer);
	pGContext->IASetVertexBuffers(0, 1, &vBuffer.buffer, &stride, &offset);
	pGContext->IASetIndexBuffer(iBuffer.getResource(), DXGI_FORMAT_R16_UINT, 0);

	pGContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	pGContext->VSSetShader(shader->pVertexShader, 0, 0);
	pGContext->PSSetShader(shader->pPixelShader, 0, 0);
	pGContext->VSSetConstantBuffers(0, 1, &cBuffer.buffer);
	pGContext->PSSetConstantBuffers(0, 1, &cBuffer.buffer);
	pGContext->PSSetShaderResources(0, 1, &fontTexture->tex);

	pGContext->DrawIndexed(6, 0, 0);
};
 