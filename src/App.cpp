#include "App.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "MouseEvent.h"
#include <stdio.h>
namespace App{
	GLuint winId;

	bool openglInitialized = false;
	float2 mousePrevPos = float2(0,0);
	int mouseButtonState = 0;

	IBase* basePanel;
	bool reRender = false;


	
	void IdleFunctionToRender();
	void OnSpecialKeyPressed(int key, int x, int y);
	void OnKeyPressed(unsigned char key, int x, int y);
	void OnMouseMove(int x, int y);
	void OnPassiveMouseMove(int x, int y);
	void OnMousePressed(int button, int state,int x, int y);
	void ResizeWindow(int width, int height);
	void Render();
}





void App::IdleFunctionToRender(){

	glutPostRedisplay();
	glutIdleFunc(NULL);

	reRender = false;

}

void App::RenderAgain(){

	if(reRender==false){
		glutIdleFunc(IdleFunctionToRender);
		reRender = true;
	}

}


void App::SetBasePanel(IBase* basePanel_){
	basePanel = basePanel_;

}

void App::OnSpecialKeyPressed(int key, int x, int y){
}

void App::OnKeyPressed(unsigned char key, int x, int y){

	printf("Pressed %d\n",key);	
	switch(key){
		case 27:
			glutDestroyWindow(winId);
			exit(0);
			break;

	}

	glutPostRedisplay();

}

void App::OnMouseMove(int x, int y){

	float xf = (float)x;
	float yf = (float)y;

	float2 delPos = float2(xf-mousePrevPos.x, yf-mousePrevPos.y);
	mousePrevPos.x = xf;
	mousePrevPos.y = yf;

	basePanel->OnMouseMove(mousePrevPos,delPos,mouseButtonState);
	

}

void App::OnPassiveMouseMove(int x, int y){

}

void App::OnMousePressed(int button, int state, int x, int y){
	float2 pos = float2(x,y);
	if(state==GLUT_DOWN){
		basePanel->OnMouseDown(button, pos);
	}else if(state == GLUT_UP){
		basePanel->OnMouseUp(button,pos);
	}

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

	mousePrevPos = float2(pos);
}

void App::ResizeWindow(int width, int height){

	glViewport(0,0,width, height);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,height,0,-1.0,1.0);

	float2 pos = float2(width/2,height/2);
	float2 size =float2(width, height);
	basePanel->SetContainingRectangle(size, pos);

}

void App::Render(){
	glClear(GL_COLOR_BUFFER_BIT);
	basePanel->Render();
	glFlush();


}

bool App::InitializeOpenGl(char *appName,int width, int height){

	if(openglInitialized == true){
		return true;
	}

	int cnt = 0;
	glutInit(&cnt,NULL);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(width,height);
	winId = glutCreateWindow(appName);
	glutFullScreen();
	return true;
}

void App::StartApp(){
	glDepthFunc(GL_NEVER);
	glutDisplayFunc(Render);	

	glutReshapeFunc(ResizeWindow);

	glutSpecialFunc(OnSpecialKeyPressed);
	glutKeyboardFunc(OnKeyPressed);
	glutMouseFunc(OnMousePressed);
	glutMotionFunc(OnMouseMove);
	glutPassiveMotionFunc(OnPassiveMouseMove);

	glutMainLoop();	

	

}
