#include "StateButton.h"
#include <SOIL/SOIL.h>
#include<stdio.h>


GLuint StateButton::textureId=0;


StateButton::StateButton(){
	SetColor(float3(0,0,0));
	state = 0;

	CreateTexture();
	
	SetVerticalAllignment(Stretch);
	SetHorizontalAllignment(Stretch);
}

void StateButton::SetColor(float3 color_){

	color = color_;
}

void StateButton::CreateTexture(){

	if(textureId) return;

	int imgWid, imgHei;
	unsigned char* imgData = SOIL_load_image("/home/x/gitmy/btn.png",&imgWid,&imgHei,NULL,0);
	glGenTextures(1,&textureId);
	glBindTexture(GL_TEXTURE_2D,textureId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWid, imgHei, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);	


	printf("Loaded Image having size %d %d \n",imgWid, imgHei);	

}


bool StateButton::Render(){

	glColor3fv((float*)(&color));
	glColor3f(1.0f,1.0f,1.0f);	


	glBindTexture(GL_TEXTURE_2D,textureId);
	glEnable(GL_TEXTURE_2D);

	if(state==1 ){
		printf("Renderingfor state 1\n");
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
			glTexCoord2f(0.0f,1.0f);
			glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
			glTexCoord2f(0.5f,1.00f);
			glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
			glTexCoord2f(0.5f,0.0f);
			 glVertex2f(pos.x+size.x/2,pos.y - size.y/2);
		glEnd();
	}else{
		printf("Rendering for state 0\n");

		glBegin(GL_QUADS);
			glTexCoord2f(0.5f,0.0f);
			glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
			glTexCoord2f(0.5f,1.0f);
			glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
			glTexCoord2f(1.0f,0.0f);
			 glVertex2f(pos.x+size.x/2,pos.y - size.y/2);
	
		glEnd();


	}
	return true;
}

bool StateButton::OnMouseDown (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;


	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		printf("Button at %f %f clicked \n", pos.x, pos.y);
		
		MouseEventArg me;
		me.button = LeftButton;
		me.state = Pressed;
		mouseEvent(me);

		state = 1-state;
		App::RenderAgain();
		printf("Button stae %d \n",state);

		return true;
	}else{
		return false;
	}


}

bool StateButton::OnMouseUp (int button, float2& pos_){

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


