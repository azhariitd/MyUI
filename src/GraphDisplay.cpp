#include "GraphDisplay.h"

#include<stdio.h>


GraphDisplay::GraphDisplay(){
	bgColor = float3(0.8f,0.8f,0.8f);
	axisColor = float3(0.1f,0.1f,0.2f);
	fgColor = float3(0.2f,0.3f,1.0f);

	xAxisOffset =0.1f;
	yAxisOffset = 0.1f;

	vertexBufferId = 0;

	float sin[100];
	for(int i=0;i<100;i++){

		sin[i] = sinf(2.0f*PI*(float)i/50.0f);
	}

	SetData(sin,100,-50,50,-1.1f,1.1f);	
}

void GraphDisplay::SetColor(float3 color_){

//	color = color_;
	bgColor = float3(1.0f,1.0f,1.0f);
}
bool GraphDisplay::Render(){

	//render background
	glColor3fv((float*)(&bgColor));

	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(pos.x -0.9f* 0.5f*size.x , pos.y+ 0.9f*0.5f*size.y,0);
	glScalef(0.9f*size.x,-0.9f*size.y,1.0f);

	//render axis
	glColor3fv((float*)(&axisColor));
	glBegin(GL_LINES);
		glVertex2f(0.0f,xAxisOffset);
		glVertex2f(1.0f,xAxisOffset);
		glVertex2f(yAxisOffset,0.0f);
		glVertex2f(yAxisOffset,1.0f);

	glEnd();

	if(vertexBufferId!=0){
	
		glColor3fv((float*)(&fgColor));	
		glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
		glVertexPointer(2,GL_FLOAT,0,NULL);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_LINE_STRIP,0,plotVertexSize);
	}


	glPopMatrix();	

	return true;
}

bool GraphDisplay::OnMouseDown (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;


	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		return true;
	}else{
		return false;
	}


}

bool GraphDisplay::OnMouseUp (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;


	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		return true;
	}else{
		return false;
	}


}

void GraphDisplay::SetData(float* dataArray, int arraySize, float xMin, float xMax, float yMin, float yMax){


	if(xMin >0) yAxisOffset = 0;
	else if(xMax <0) yAxisOffset =1;
	else yAxisOffset = (0-xMin)/(xMin-xMin);

	if(yMin >0) xAxisOffset =0;
	else if(yMax<0) xAxisOffset =1.0f;
	else xAxisOffset = (0-yMin)/(yMax - yMin);


	float2 data[arraySize];
	for(int i=0;i<arraySize;i++){
		data[i].y = (dataArray[i]-yMin)/(yMax-yMin);
		data[i].x = (float)i/(float)arraySize;


	}

	glGenBuffers(1,&vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER,2*sizeof(float)*arraySize,data,GL_STATIC_DRAW);	

	plotVertexSize = arraySize;
}
