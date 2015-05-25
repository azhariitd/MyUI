#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//#include "StackPanel.h"
#include "Slider.h"
#include "Rect.h"
#include "GraphDisplay.h"
#include "MouseEvent.h"
#include "Canvas.h"
#include "StateButton.h"
#include "Grid.h"
#include "PlotWrap.h"
#include "TextBox.h"
#include "FontManager.h"

Grid* sp;
void init(){
	PlotWrap *p = new PlotWrap();
	sp = new Grid();
	sp->AddRowDefinition(Relative,1.0f);
	sp->AddColumnDefinition(Relative,1.0f);
	FontManager fm =  FontManager();
	FontInfo* fi = fm.OpenFont("a.ttf",18);
//	TextBox* tb = new TextBox(fi,"Aloo lelo");
	sp->AddChild(0,0,p);
	

	p->SetHorizontalAllignment(Stretch);
	p->SetVerticalAllignment(Stretch);
	App::SetBasePanel(sp);
}

void drawUnitRectangle(){

	glBegin(GL_POLYGON);
		glVertex2f(0.0f,0.0f);
		glVertex2f(0.0f,1.0f);
		glVertex2f(0.50f,1.0f);
		glVertex2f(0.50f,0.0f);
	glEnd();	

}

void RenderScene(){
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,1.0f,0.0f);


	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);	
	//drawUnitRectangle();
	sp->Render();
	printf("Rendered \n");	
	glFlush();

}

int main(int argc, char** argv){
	
	App::InitializeOpenGl("My Window",400,300);
	init();
	App::StartApp();
	

	return 0;
}


