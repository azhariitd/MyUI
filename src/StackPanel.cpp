#include "StackPanel.h"

StackPanel::StackPanel(){
	IBase();
	orientation  = Vertical;

}

void StackPanel::SetContainingRectangle(float2& size_, float2& pos_){
	IBase::SetContainingRectangle(size_,pos_);

	UpdateChildenMetrics();
}


void StackPanel::UpdateChildenMetrics(){

	int totalChild = children.size();

	if(orientation == Vertical){
		float2 childSize = float2(size.x,size.y/totalChild);
		int i=0;
		float top = pos.y-0.5f*size.y;
		float2 newPos = float2(pos.x,top+0.5f*childSize.y );
		for(;i<totalChild;i++){
			
			children.at(i)->SetContainingRectangle(childSize,newPos);
			newPos.y+=childSize.y;


		}


	}
	else if(orientation == Horizontal){
		float2 childSize = float2(size.x/totalChild,size.y);
		int i=0;
		float left = pos.x-0.5f*size.x;
		float2 newPos = float2(left+0.5f*childSize.x,pos.y);
		for(;i<totalChild;i++){
			
			children.at(i)->SetContainingRectangle(childSize,newPos);
			newPos.x+=childSize.x;


		}


	}
}

void StackPanel::SetOrientation(Orientation orientation_){
	orientation = orientation_;
	UpdateChildenMetrics();
}
