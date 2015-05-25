#include "Canvas.h"

#include<stdio.h>

Canvas::Canvas(){

	bgColor = float3(0.1f,0.1f,0.9f);
	fgColor = float3(0.9f,0.1f,0.1f);

	selected = NULL;
	mouseOp = None;
}

void Canvas::SetColor(float3 color_){
	
	bgColor = color_;
	//color = color_;
}
bool Canvas::Render(){

	glColor3fv((float*)(&bgColor));
	//glColor3f(1.0f,1.0f,1.0f);	

	printf("Rendering rect at %f %f %f %f\n", pos.x, pos.y, size.x, size.y);

	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();




	std::vector<ChildData*>::iterator cur = canvasChildren.begin();
	std::vector<ChildData*>::iterator end = canvasChildren.end();

	
	for(;cur!=end;cur++){
		(*cur)->child->Render();

		//draw rect here
		float2 *childPos = &((*cur)->absPos);
		float2 *childSize = &((*cur)->size);
	
		printf("Drawinc child at %3.3f,%3.3f; %3.3f,%3.3f\n",childPos->x,  childPos->y, childSize->x, childSize->y);

	
		glColor3fv((float*)(&fgColor));
		glBegin(GL_LINE_LOOP);
			glVertex2f(childPos->x - 0.5f*childSize->x, childPos->y -0.5f*childSize->y);
			glVertex2f(childPos->x - 0.5f*childSize->x, childPos->y +0.5f*childSize->y);
			glVertex2f(childPos->x + 0.5f*childSize->x, childPos->y +0.5f*childSize->y);
			glVertex2f(childPos->x + 0.5f*childSize->x, childPos->y -0.5f*childSize->y);
		glEnd();
	}



	return true;
}

bool Canvas::CheckChildrenDown(int button,float2& pos_){
	std::vector<ChildData*>::iterator cur = canvasChildren.begin();
	std::vector<ChildData*>::iterator end = canvasChildren.end();

	
	for(;cur!=end;cur++){
		ChildData* curChild = *cur;

		float xDif = pos_.x - curChild->absPos.x + 0.5f*curChild->size.x;		
		 float yDif = pos_.y - curChild->absPos.y +0.5f*curChild->size.y;

		if(xDif>0 && xDif < curChild->size.x &&
			yDif > 0 && yDif < curChild->size.y){
			selected = curChild;
			if(xDif < RESWIDTH) mouseOp =ResizeLeft;	
			else if(xDif>curChild->size.x-RESWIDTH) mouseOp =ResizeRight;

			if(yDif<RESWIDTH) mouseOp =(MouseMoveOp) ( (int)mouseOp|(int)ResizeTop);
			else if(yDif>curChild->size.y-RESWIDTH) mouseOp= (MouseMoveOp)((int)ResizeBotton | (int)mouseOp);;

			if(mouseOp==0){
				if(yDif < MOVEWIDTH) mouseOp= Move;	
				else {
					mouseOp=None;
					selected =NULL;
					curChild->child->OnMouseDown(button,pos_);
				}
			}


			printf("State is %x \n",(int)mouseOp);
			return true;
		}
		
	}	
	

	return false;
}


bool Canvas::OnMouseDown (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;


	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		if(CheckChildrenDown(button,pos_)) glutPostRedisplay();	


		return true;
	}else{
		return false;
	}


}

bool Canvas::OnMouseUp (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;

	if(selected!=NULL) selected =NULL;
	if(mouseOp!=None) mouseOp =None;

	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		return true;
	}else{
		return false;
	}


}

bool Canvas::OnMouseMove(float2& pos_, float2& delPos, int mouseState){


	if(mouseOp!=None){
		float2* childSize = &(selected->size);
		float2* childRelPos= &(selected->relPos);

		if(mouseOp&ResizeLeft){
			childSize->x -= delPos.x;
			childRelPos->x +=delPos.x*0.5f;

		}else if(mouseOp&ResizeRight){
			childSize->x += delPos.x;
			childRelPos->x += delPos.x*0.5f;
		}

		if(mouseOp&ResizeTop){
			childSize->y -= delPos.y;
			childRelPos->y += 0.5f*delPos.y;
		}else if(mouseOp&ResizeBotton){
			childSize->y += delPos.y;
			childRelPos->y += 0.5f*delPos.y;
		}
		
		if(mouseOp&Move){
			childRelPos->x+=delPos.x;
			childRelPos->y += delPos.y;
		}


		selected->absPos.x = childRelPos->x + pos.x -0.5f*size.x;
		selected->absPos.y = childRelPos->y + pos.y-0.5f*size.y;
		selected->child->SetContainingRectangle(selected->size,selected->absPos);


		glutPostRedisplay();


	}

	return true;


}


bool Canvas::AddChild(IBase* child){

	float2 pos_ = float2(size.x*RandFloat(), size.y*RandFloat());
	float2 size_ = float2(size.x*RandFloat(),size.y*RandFloat());
	

	return AddChild(child,pos_,size_);
}


bool Canvas::AddChild(IBase* child, float2& pos_, float2& size_){


	ChildData* cd = new ChildData();
	cd->relPos = pos_;

	float2 absPos;
	absPos.x  = pos_.x + pos.x -0.5f*size.x;
	absPos.y = pos_.y + pos.y -  0.5f*size.y;

	cd->size = size_;
	cd->relPos = pos_;
	cd->absPos = absPos;
	cd->child = child;
	canvasChildren.push_back(cd);
	cd->child->SetContainingRectangle(size_,absPos);


	return true;
}

bool Canvas::RemoveChild(IBase* child){

	std::vector<ChildData*>::iterator cur = canvasChildren.begin();
	std::vector<ChildData*>::iterator end = canvasChildren.end();
	
	for(;cur!=end;cur++){
		if((*cur)->child == child){
			canvasChildren.erase(cur);
			delete(*cur);		
			return true;
		}
	}

	return false;
}


void Canvas::SetContainingRectangle(float2& size_, float2& pos_){

	IBase::SetContainingRectangle(size_, pos_);

	std::vector<ChildData*>::iterator cur = canvasChildren.begin();
	std::vector<ChildData*>::iterator end = canvasChildren.end();
	
	float delX = pos.x - 0.5f*size.x;
	float delY = pos.y - 0.5f*size.y;

	for(;cur!=end;cur++){
		(*cur)->absPos.x = (*cur)->relPos.x+delX;
		(*cur)->absPos.y = (*cur)->relPos.y + delY;

		(*cur)->child->SetContainingRectangle((*cur)->size,(*cur)->absPos);
	}
	



}
