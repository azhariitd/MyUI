#include "TextBox.h"
#include<stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

TextBox::TextBox(FontInfo *font_){
	SetColor(float3(0,1.0f,0));
	font = font_;

}

TextBox::TextBox(FontInfo* font_, char *text_){
	font = font_;
	strcpy(text, text_);
	SetColor(float3(0.0f,1.0f,0.0f));

}

void TextBox::SetText(char* text_){
	strcpy(text,text_);
}

void TextBox::SetColor(float3 color_){

	color = float3(color_);
}

bool TextBox::Render(){

	glColor3fv((float*)(&color));
	glColor3f(1.0f,1.0f,1.0f);	


	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();

	glColor3f(0.0f,0.0f,0.0f);
	
	glPushMatrix();
	glTranslatef(pos.x - 0.5f*size.x,pos.y,0.0f);
	font->PrintText(text);
	glPopMatrix();

	return true;
}

bool TextBox::OnMouseDown (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;


	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		printf("Button at %f %f clicked \n", pos.x, pos.y);
		
		MouseEventArg me;
		me.button = LeftButton;
		me.state = Pressed;
		mouseEvent(me);

		return true;
	}else{
		return false;
	}


}

bool TextBox::OnMouseUp (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;


	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		MouseEventArg me;
		me.button = LeftButton;
		me.state = Released;
		mouseEvent(me);

		return true;
	}else{
		return false;
	}


}


