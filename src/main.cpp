#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "StackPanel.h"
#include "Rect.h"


StackPanel* sp;

void OnSpecialKeyPressed(int key, int x, int y)
{
}



void OnKeyPressed(unsigned char key, int x, int y){
}

void OnMousePressed(int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON){
		if(state==GLUT_UP) printf("Left button up at %d %d\n",x,y);
		else if(state==GLUT_DOWN) printf("Left button down at %d %d\n",x,y);
	}else

	if(button == GLUT_RIGHT_BUTTON){
		if(state==GLUT_UP) printf("Right button up at %d %d\n",x,y);
		else if(state==GLUT_DOWN) printf("Right button down at %d %d\n",x,y);
	}else
	if(button == GLUT_MIDDLE_BUTTON){
		if(state==GLUT_UP) printf("Middle button up at %d %d\n",x,y);
		else if(state==GLUT_DOWN) printf("Middle button down at %d %d\n",x,y);
	}
}

void ChangeSize(int width_, int height_){

	glViewport(0,0, width_,height_);
	
	float2 size = float2(width_,height_);
	float2 pos = float2(width_/2,height_/2);
	printf("Width Height %f %f\n",size.x, size.y);
	sp->SetContainingRectangle(size, pos);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width_, height_, 0, -1.0, 1.0);
}

void init(){
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	sp = new StackPanel();
	sp->SetOrientation(Vertical);
	StackPanel* sp2 = new StackPanel();
	sp2->SetOrientation(Horizontal);
	sp->AddChild(sp2);
	for(int i=0;i<5;i++){
		Rect *rt = new Rect();
		sp->AddChild(rt);

		
		rt->SetColor(float3(i/4,i/3,(i+1)/2));

	}

	for(int i=0;i<5;i++){
		Rect *rt = new Rect();
		sp2->AddChild(rt);

		
		rt->SetColor(float3(i/4,i/3,(i+1)/2));

	}


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
	
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f,1.0f,0.0f);


	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);	
	//drawUnitRectangle();
	sp->Render();
	printf("Rendered \n");	
	glFlush();

}

int main(int argc, char** argv){
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH );
	glutInitWindowSize(600,400);
	glutCreateWindow("MyUi");

	init();
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(OnSpecialKeyPressed);
	glutKeyboardFunc(OnKeyPressed);
	glutMouseFunc(OnMousePressed);
	glutMainLoop();

	

	return 0;
}
