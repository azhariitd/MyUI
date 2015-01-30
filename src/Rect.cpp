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

bool Rect::OnMouseDown (int button, float2& pos_){

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

bool Rect::OnMouseUp (int button, float2& pos_){

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


