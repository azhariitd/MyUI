#include "PlotWrap.h"

#include<stdio.h>
#include "PlotScroll.h"

PlotWrap::PlotWrap(){
	Grid();

	SetColor(float3(RandFloat(),RandFloat(),RandFloat()));
	
	//Create UI
	AddRowDefinition(Relative,1.0f);
	AddRowDefinition(Absulute,80.0f);
	AddColumnDefinition(Absulute,80.0f);
	AddColumnDefinition(Relative,1.0f);
	PlotScroll* ps = new PlotScroll(Vertical);
	AddChild(0,0,ps);
	PlotScroll* ps2 = new PlotScroll(Horizontal);
	AddChild(1,1,ps2);

	plot = new Plot();
	AddChild(1,0,plot);

	ps2->plotScrollEvent += new Event<bool,PlotScrollEventArgs&>::T<PlotWrap>(this,&PlotWrap::OnHorizontalScrollChange);	

}

void PlotWrap::SetColor(float3 color_){

	color = float3(color_);
}
bool PlotWrap::Render(){

	glColor3fv((float*)(&color));
	//glColor3f(1.0f,1.0f,1.0f);	


	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();

	Grid::Render();

	return true;
}

bool PlotWrap::OnMouseDown (int button, float2& pos_){
	Grid::OnMouseDown(button,pos_);

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

bool PlotWrap::OnMouseUp (int button, float2& pos_){
	Grid::OnMouseUp(button,pos_);

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

bool PlotWrap::OnHorizontalScrollChange(PlotScrollEventArgs &arg){
	printf("Callback called\n");	
	plot->SetValues(arg.offset,arg.scale);

	return false;
};
