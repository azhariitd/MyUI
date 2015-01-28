#include "Rect.h"

#include<stdio.h>

float Rf(){
	return (float)rand()/(float) RAND_MAX;
}



void Rect::SetColor(float3 color_){

	//color = color_;
	color = float3(Rf(),Rf(), Rf());
}
bool Rect::Render(){

	glColor3fv((float*)(&color));
	//glColor3f(1.0f,1.0f,1.0f);	

	printf("Rendering rect at %f %f %f %f\n", pos.x, pos.y, size.x, size.y);

	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();

	return true;
}
