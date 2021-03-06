#include "Slider.h"

#include<stdio.h>

float Rf2(){
	return (float)rand()/(float)RAND_MAX;
}

Slider::Slider(){
	fgColor = float3(Rf2(),Rf2(),Rf2());
	bgColor = float3(Rf2(),Rf2(),Rf2());
	valNormalized = 0;

	orientation = SlVertical;
}

void Slider::SetColor(float3 color_){

	//color = color_;
}
bool Slider::Render(){

	glColor3fv((float*)(&bgColor));
	//glColor3f(1.0f,1.0f,1.0f);	


	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();

	glColor3fv((float*)(&fgColor));
	//glColor3f(1.0f,1.0f,1.0f);	
	if(orientation == SlVertical){
		float sizey = size.y - (float)HANDLEMARGIN;
		glBegin(GL_QUADS);
			glVertex2f(pos.x - HANDLEWIDTH*0.5f ,pos.y - sizey/2 + sizey*valNormalized - 0.5f*HANDLEHEIGHT);
			glVertex2f(pos.x + HANDLEWIDTH*0.5f ,pos.y - sizey/2 + sizey*valNormalized - 0.5f*HANDLEHEIGHT);
			glVertex2f(pos.x + HANDLEWIDTH*0.5f ,pos.y - sizey/2 + sizey*valNormalized + 0.5f*HANDLEHEIGHT);
			glVertex2f(pos.x - HANDLEWIDTH*0.5f ,pos.y - sizey/2 + sizey*valNormalized + 0.5f*HANDLEHEIGHT);
		glEnd();

	 }else if(orientation == SlHorizontal){
		float sizex = size.x - (float)HANDLEMARGIN;
		glBegin(GL_QUADS);
			glVertex2f(pos.x-sizex/2 + valNormalized*sizex+0.5f*HANDLEHEIGHT ,pos.y + 0.5f*HANDLEHEIGHT);
			glVertex2f(pos.x-sizex/2 + valNormalized*sizex-0.5f*HANDLEHEIGHT ,pos.y + 0.5f*HANDLEHEIGHT);
			glVertex2f(pos.x-sizex/2 + valNormalized*sizex-0.5f*HANDLEHEIGHT ,pos.y - 0.5f*HANDLEHEIGHT);
			glVertex2f(pos.x-sizex/2 + valNormalized*sizex+0.5f*HANDLEHEIGHT ,pos.y - 0.5f*HANDLEHEIGHT);
		
			glEnd();


	 }
	return true;
}

bool Slider::OnMouseDown (int button, float2& pos_){


	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;


	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		printf("Button at %f %f clicked \n", pos.x, pos.y);
		
		MouseEventArg me;
		me.button = LeftButton;
		me.state = Pressed;
		mouseEvent(me);

		
		if(orientation==SlVertical){
			float sizey = size.y - (float)HANDLEMARGIN;
			float newVal  = (pos_.y-pos.y +0.5f*sizey)/sizey;
			if(newVal <= 1.0f && newVal >=0.0f) valNormalized = newVal;
		}else if(orientation == SlHorizontal){
			float sizex = size.x - (float)HANDLEMARGIN;
			float newVal = (pos_.x-pos.x + 0.5f*sizex)/sizex;
			if(newVal <=1.0f && newVal >=0.0f) valNormalized = newVal;
		}	

		glutPostRedisplay();

		return true;
	}else{
		return false;
	}


}

bool Slider::OnMouseUp (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;


	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		MouseEventArg me;
		me.button = LeftButton;
		me.state = Released;
		mouseEvent(me);

		glutPostRedisplay();
		return true;
	}else{
		return false;
	}


}


