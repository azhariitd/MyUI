#include "IBase.h"


IBase::IBase(){
	horAlignment = Center;
	verAlignment = Center;

	children.clear();
	absSize = float2(100.0f,100.0f);

}

float IBase::RandFloat(){

	return (float)rand()/(float)RAND_MAX;
}

///////////////////////////////
//REGION BASE DEFINITIONS /////
///////////////////////////////

//......#Region Metrics 
void IBase::SetContainingRectangle(float2& size_, float2& pos_){

	if(horAlignment==Stretch || size_.x < size.x) size.x = size_.x;
	else size.x = absSize.x;
	if(verAlignment==Stretch || size_.y < size.y)  size.y = size_.y;
	else size.y = absSize.y;

		
	if(verAlignment== Top) pos.y = pos_.y - 0.5f*size_.y + 0.5f*size.y;
	else if(verAlignment==Center) pos.y = pos_.y;
	else if(verAlignment==Bottom) pos.y = pos_.y + 0.5f*size_.y-0.5f*size.y;
	else if(verAlignment==Stretch) pos.y = pos_.y;



	if(horAlignment== Left) pos.x = pos_.x - 0.5f*size_.x + 0.5f*size.x;
	else if(horAlignment==Center) pos.x = pos_.x;
	else if(horAlignment==Right) pos.x = pos_.x + 0.5f*size_.x-0.5f*size.x;
	else if(horAlignment==Stretch) pos.x = pos_.x;
}

void IBase::SetHorizontalAllignment(Allignment alignment){
	if(horAlignment!=alignment) horAlignment=alignment;
}


void IBase::SetVerticalAllignment(Allignment alignment){
	if(verAlignment!=alignment) verAlignment=alignment;
}

float2 IBase::GetAbsSize(){
	return absSize;
}

float2 IBase::GetSize(){
	return size;
}

//.......#Region userdata
bool IBase::AddUserData(int key, void* data){

	if(userDataMap.find(key)==userDataMap.end()){
		return false;
	}else{
		userDataMap[key] = data;
	}

	return false;
}

bool IBase::DeleteUserData(int key){

	if(userDataMap.find(key)==userDataMap.end()){
		return false;
	}else{
		userDataMap.erase(key);
	}

	return false;
}

void* IBase::GetUserData(int key){

	if(userDataMap.find(key)==userDataMap.end()){
		return NULL;	
	}else{
		return userDataMap[key];
	}

	return NULL;
}


//......#Region children
bool IBase::AddChild(IBase* child){
	children.push_back(child);
	child->SetParent(this);
	return true;
}

bool IBase::RemoveChild(IBase* child){
	
	for(std::vector<IBase*>::iterator cur = children.begin();cur!=children.end();cur++){
		if(*cur==child){
			children.erase(cur);
			return true;
		}

	}

	return false;
}

void IBase::SetParent(IBase* parent_){
	if(parent_!=parent) parent = parent_;

}


//....#region Render
bool IBase::Render(){
	for(std::vector<IBase*>::iterator cur = children.begin();cur!=children.end();cur++){
		(*cur)->Render();
	}

	return true;
}


//......#region Input handler
bool IBase::OnMouseDown (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;

	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){

		for(std::vector<IBase*>::iterator cur = children.begin();cur!=children.end();cur++){
			if((*cur)->OnMouseDown(button,pos_)) return true;		
		}
		return false;

	}else{
		return false;
	}
}
bool IBase::OnMouseMove(float2& pos_, float2& delPos, int mouse){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;

	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){

		for(std::vector<IBase*>::iterator cur = children.begin();cur!=children.end();cur++){
			if((*cur)->OnMouseMove(pos_,delPos,mouse)) return true;		
		}
		return false;

	}else{
		return false;
	}



}


bool IBase::OnMouseUp (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;

	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){

		for(std::vector<IBase*>::iterator cur = children.begin();cur!=children.end();cur++){
			if((*cur)->OnMouseUp(button,pos_)) return true;		
		}
		return false;

	}else{
		return false;
	}
}
