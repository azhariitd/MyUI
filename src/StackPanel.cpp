#include "StackPanel.h"

StackPanel::StackPanel(){
	IBase();
	orientation  = Vertical;
	verAlignment = Stretch;
}

void StackPanel::SetContainingRectangle(float2& size_, float2& pos_){
	IBase::SetContainingRectangle(size_,pos_);

	UpdateChildenMetrics();
}


void StackPanel::UpdateChildenMetrics(){

	int totalChild = children.size();

	if(orientation == Vertical){
		int i=0;
		float top = pos.y-0.5f*size.y;
		float2 newPos = float2(pos.x,top );
		for(;i<totalChild;i++){
			float2 childSize = children.at(i)->GetAbsSize();				newPos.y += 0.5f*childSize.y;
			childSize.x = size.x;
				
			children.at(i)->SetContainingRectangle(childSize,newPos);
			newPos.y+=childSize.y*0.5f;


		}


	}
	else if(orientation == Horizontal){
		int i=0;
		float left = pos.x-0.5f*size.x;
		float2 newPos = float2(left,pos.y);
		for(;i<totalChild;i++){
			float2 childSize = children.at(i)->GetAbsSize();
			newPos.x+= 0.5f* childSize.y;
			childSize.y = size.y;

			children.at(i)->SetContainingRectangle(childSize,newPos);
			newPos.x+=childSize.x * 0.5f;


		}


	}
}

void StackPanel::SetOrientation(Orientation orientation_){
	orientation = orientation_;
	UpdateChildenMetrics();
}

bool StackPanel::Render(){
	glColor3f(0.5f,0.5f,1.0f);


	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();

	return IBase::Render();

}
