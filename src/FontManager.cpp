#include<stdio.h>
#include <string.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include "helper.h"

#include "FontManager.h"

using namespace std;


FontInfo::FontInfo(char *fileName_, int size_){
	
	assert(strlen(fileName_) < 32);
	strcpy(fileName,fileName_);
	size = size_;
	
	CreateDisplayList();

}

bool FontInfo::IsFont(char *fileName_, int size_){
	return (!strcmp(fileName_, fileName) && size==size_);
}

void FontInfo::MakeTexture(FT_Face face, char ch, GLuint listBase, GLuint* textureId){
	if(FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT)){
		cerr<< "Failed to load glyph " << endl;
		return;
	}

	FT_Glyph glyph;
	if(FT_Get_Glyph(face->glyph,&glyph)){
		cerr << "Failed to get glyph for" << endl;
	
	}

	FT_Glyph_To_Bitmap(&glyph,ft_render_mode_normal,0,1);
	FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;

	FT_Bitmap& bitmap = bitmapGlyph->bitmap;
	glyphWidth[ch] = (float)bitmap.width;
	int width = NextPowerOf2(bitmap.width);
	int height = NextPowerOf2(bitmap.rows);

	GLubyte* expandedData = new GLubyte[2*width*height];
	
	for(int j=0;j<height;j++){
		for(int i=0;i<width;i++){
			expandedData[2*(i+j*width)] =  expandedData[2*(i+j*width)+1] = (i>=bitmap.width || j>=bitmap.rows) ? 0:bitmap.buffer[i+bitmap.width*j];
		}
	}

	glBindTexture(GL_TEXTURE_2D,*textureId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_LUMINANCE_ALPHA,GL_UNSIGNED_BYTE,expandedData);

	delete [] expandedData;

	glNewList(listBase+ch,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D,*textureId);
	glPushMatrix();
	glTranslatef(bitmapGlyph->left,0  ,0.0f);
	glTranslatef(0,bitmapGlyph->top - bitmap.rows  ,0.0f);
	float x = (float)bitmap.width/(float)width;
	float y = (float)bitmap.rows/(float)height;

	glBegin(GL_QUADS);
		glTexCoord2d(0.0f,y); glVertex2f(0,bitmap.rows);
		glTexCoord2d(0.0f,0.0f); glVertex2f(0,0);
		glTexCoord2d(x,0.0f); glVertex2f(bitmap.width,0);
		glTexCoord2d(x,y); glVertex2f(bitmap.width,bitmap.rows);
	glEnd();
	
	glPopMatrix();
	glTranslatef(face->glyph->advance.x>>6,0.0f,0.0f);
	glEndList();	




}





bool FontInfo::CreateDisplayList(){

	FT_Library ft;
	if(FT_Init_FreeType(&ft)){
		cerr << "Failed to init freetype" << endl;
		return false;
	}

	FT_Face face;
	if(FT_New_Face(ft,fileName,0,&face)){
		cerr << "Failed to open font: " << fileName<< endl;
		return false;
	}
	
	FT_Set_Char_Size(face,size <<6, size<<6 , 96,96);

	textures = new GLuint[128];
	listBase = glGenLists(128);
	glGenTextures(128,textures);
	glyphWidth = new float[128];


	for(unsigned char i=0;i<128;i++){
		MakeTexture(face,i,listBase,textures+i);
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	return true;

}

GLuint FontInfo::GetListBase(){
	return listBase;
}

float FontInfo::WidthOfString(char *string){

	float totalWidth = 0.0f;	

	while(*string){
		totalWidth += glyphWidth[*string];
		string++;
	}	
	return totalWidth;
}

void FontInfo::PrintText(char *text){
;
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glListBase(listBase);
	glPushMatrix();
	glCallLists(strlen(text),GL_UNSIGNED_BYTE,text);	
	glPopMatrix();	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}



void FontInfo::DeleteFont(){
	glDeleteLists(listBase,128);
	glDeleteTextures(128,textures);
	delete[] textures;

}


std::vector<FontInfo*> FontManager::openedFonts ;



FontManager::FontManager(){
		

}

FontInfo* FontManager::OpenFont(char* fileName, int size){

	std::vector<FontInfo*>::iterator cur = openedFonts.begin();
	std::vector<FontInfo*>::iterator end = openedFonts.end();
	for(;cur!=end;cur++){
		if((*cur)->IsFont(fileName, size)){
			return *cur;
		}

	}

	FontInfo *fi = new FontInfo(fileName, size);
	openedFonts.push_back(fi);
	return fi;

}

void FontManager::CloseFont(char* fileName, int size){

	std::vector<FontInfo*>::iterator cur = openedFonts.begin();
	std::vector<FontInfo*>::iterator end = openedFonts.end();
	for(;cur!=end;cur++){
		if((*cur)->IsFont(fileName, size)){
			delete((*cur));
			openedFonts.erase(cur);
			return ;
		}

	}



}



