
#include <vector>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include FT_FREETYPE_H

#ifndef FONTMGR_INCLUDE__
#define FONTMGR_INCLUDE__

class FontInfo{

private:
	char fileName[32];
	int size;
	GLuint *textures;
	GLuint listBase;
	float *glyphWidth;
	void MakeTexture(FT_Face face, char ch, GLuint listBase, GLuint *textureId);

	bool CreateDisplayList();

public:
	FontInfo(char *fileName_, int size);
	bool IsFont(char *fileName_, int size);
	GLuint GetListBase();
	void DeleteFont();
	float WidthOfString(char* string);
	void PrintText(char *string);


};




class FontManager{

private:	
	static std::vector<FontInfo*> openedFonts;

public:
	FontManager();
	FontInfo* OpenFont(char *fileName, int size);
	void CloseFont(char *fileName, int size);


};
#endif
