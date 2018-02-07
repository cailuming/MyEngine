#include"CSpriteFont.h"

CSpriteFont::CSpriteFont() {
}

CSpriteFont::~CSpriteFont() {
}
CSpriteFont *CSpriteFont::font=0;

CSpriteFont *CSpriteFont::create() {
	return font;
};
 
void CSpriteFont::destroy() {

};
 