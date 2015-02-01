#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "StackPanel.h"
#include "Slider.h"
#include "Rect.h"

#include "MouseEvent.h"

StackPanel* sp;
int mouseButtonState;

void OnSpecialKeyPressed(int key, int x, int y)
{
}



void OnKeyPressed(unsigned char key, int x, int y){
}

void OnMouseMove(int x, int y){
	printf("Mouse moved with state %x\n",mouseButtonState);

}

void OnPassiveMouseMove(int x, int y){
	printf("Mouse moved passive with state %x\n",mouseButtonState);



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

	float2 pos = float2(x,y);
	if(state==GLUT_DOWN){
		sp->OnMouseDown(button, pos);
	}else if(state == GLUT_UP){
		sp->OnMouseUp(button,pos);
	}

	printf("Buttons %d %d %d\n",LeftButton,RightButton,MiddleButton);
	int mouseState = 0;
	if(button ==GLUT_LEFT_BUTTON){
		mouseState = LeftButton;
	}else if(button ==GLUT_RIGHT_BUTTON){
		mouseState = RightButton;
	}else if(button == GLUT_MIDDLE_BUTTON){
		mouseState = MiddleButton;
	}

	
	if(state == GLUT_DOWN){
		mouseButtonState |= mouseState;
	}else if(state == GLUT_UP){
		mouseButtonState &= ~mouseState;
	}
	printf("MOuse state %x %x \n", mouseState, mouseButtonState);
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

bool OnRectClicked(MouseEventArg& me){
	printf("Rect clicked \n");
	return true;

}

void init(){
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

//	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_NEVER);

	mouseButtonState = 0;

	MouseEvent::S *ev = new MouseEvent::S(OnRectClicked);

	sp = new StackPanel();
	sp->SetOrientation(Horizontal);
	StackPanel* sp2 = new StackPanel();
	sp2->SetOrientation(Horizontal);
	sp->AddChild(sp2);
	for(int i=0;i<5;i++){
		Slider* sl = new Slider();
		sp->AddChild(sl);

		

	}

	for(int i=0;i<5;i++){
		Rect *rt = new Rect();
	//	rt->mouseEvent += ev;
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
	glutMotionFunc(OnMouseMove);
	glutPassiveMotionFunc(OnPassiveMouseMove);
	glutMainLoop();

		

	return 0;
}
