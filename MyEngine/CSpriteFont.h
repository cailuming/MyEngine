#pragma once
class CSpriteFont {
private:
	CSpriteFont();
	~CSpriteFont();
public:
	static CSpriteFont *font;
	static CSpriteFont *create();
	static void destroy();
public:
	void InitFont();

};