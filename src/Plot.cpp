#include "Plot.h"

#include<stdio.h>
#include <math.h>

#define PI 3.1459

Plot::Plot(){
	minX = 0.0f;
	maxX = 1.0f;
	SetColor(float3(RandFloat(),RandFloat(),RandFloat()));
	SetVerticalAllignment(Stretch);
	SetHorizontalAllignment(Stretch);
	
	vboId = 0;
	offset = 0.0f;
	scale =  1.0f;
	prevScale = 1.0f;
}

double Plot::PlotFunc(double x){

	double sn = sin(2.0f*PI*1.0*x);
	return sn*sn;

}




void Plot::SetColor(float3 color_){

	color = float3(color_);
}
/*
void Plot::CreatePlotVertexBuffer(){



}
*/


bool Plot::Render(){
	printf("Rendering plot %f %f\n",offset,scale);
	glColor3fv((float*)(&color));
//	glColor3f(0.0f,1.0f,1.0f);	


	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();

	glColor3f(0.0f,0.0f,1.0f);

	float width = size.x;
	float height = size.y;
	int iter = width;
	float delX = (maxX-minX)/((float)iter*scale);
	float curX = minX + (maxX-minX)*offset/scale;
	float orgX = pos.x-0.5f*size.x;
	if(iter>0){
		glPushMatrix();
		glScalef(1.0f,height,1.0f);	
		glBegin(GL_LINE_STRIP);
		for(int i =0;i<iter;i++){
			glVertex2f(orgX+i,PlotFunc(curX));
			curX += delX;
		}

		glEnd();
		glPopMatrix();	
	}
	return true;
}

bool Plot::OnMouseDown (int button, float2& pos_){

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

bool Plot::OnMouseUp (int button, float2& pos_){

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

void Plot::SetValues(float offset_, float scale_){
	offset = offset_;
	scale = scale_;
	printf("Modified value\n");
}
