#include "Grid.h"

#include <stdio.h>

Grid::Grid(){
	IBase();
	verAlignment = Stretch;
	horAlignment = Stretch;

	rowInfo.clear();
	columnInfo.clear();
	gridChildren.clear();

	totalColumn = totalRow = 0;
}

void Grid::SetContainingRectangle(float2& size_, float2& pos_){
	IBase::SetContainingRectangle(size_,pos_);

	UpdateChildenMetrics();
}


void Grid::UpdateChildenMetrics(){


	float leftWidth = size.x;
	float totRatioX = 0;
	for(int i=0;i<totalColumn;i++){
		RowInfo* rw = columnInfo.at(i);
		if(rw->sizeType == Absulute){
			leftWidth -= rw->size;

		}else if(rw->sizeType == Relative){
			totRatioX += rw->size;
			
		}


	} 
	
	float pos=0;
	for(int i=0;i<totalColumn;i++){
		RowInfo* rw = columnInfo.at(i);
		if(rw->sizeType == Absulute){
			rw->absSize = rw->size;
			rw->pos = pos+ 0.5f*rw->absSize;
			pos+= rw->absSize;
		}else if(rw->sizeType == Relative){
			rw->absSize = rw->size*leftWidth/totRatioX;	
			rw->pos = pos+ 0.5f*rw->absSize;
			pos+= rw->absSize;
		}	


	}


	float leftHeight = size.y;
	float totalRatioY = 0;
	for(int i=0;i<totalRow;i++){
		RowInfo* rw = rowInfo.at(i);
		if(rw->sizeType == Absulute){
			leftHeight -= rw->size;
		}else if(rw->sizeType == Relative){
			totalRatioY += rw->size;

		}	
		
	}

	pos = 0.0f;
	for(int i=0;i<totalRow;i++){
	
		RowInfo* rw = rowInfo.at(i);
		
		if(rw->sizeType == Absulute){
			rw->absSize = rw->size;
			rw->pos = pos+ 0.5f*rw->absSize;
			pos+= rw->absSize;
		}else if(rw->sizeType == Relative){
			rw->absSize = rw->size*leftHeight/totalRatioY;	
			rw->pos = pos+ 0.5f*rw->absSize;
			pos+= rw->absSize;
		}	
	
	}


	int totalChildren = gridChildren.size();

	for(int i=0;i<totalChildren;i++){

		GridChildInfo* gcInfo = gridChildren.at(i);
		int x = gcInfo->rowNo;
		int y = gcInfo->columnNo;
		float2 cpos = float2(columnInfo.at(x)->pos, rowInfo.at(y)->pos);

		float2 csize = float2(columnInfo.at(x)->absSize, rowInfo.at(y)->absSize);
		gcInfo->child->SetContainingRectangle(csize, cpos);
	}
}

void Grid::AddRowDefinition(SizeType sizeType_, float size_){
	RowInfo *rw = new RowInfo();
	rw->sizeType = sizeType_;
	rw->size = size_;

	rowInfo.push_back(rw);
	totalRow++;

}

void Grid::AddColumnDefinition(SizeType sizeType_, float size_){
	RowInfo *rw = new RowInfo();
	rw->sizeType = sizeType_;
	rw->size = size_;

	columnInfo.push_back(rw);
	totalColumn++;
}

bool Grid::AddChild(int row, int column, IBase* child){

	if(row<0 || row >= totalRow 
	 || column < 0 || column >= totalColumn){
		return false;
	}

	GridChildInfo* gcInfo = new GridChildInfo();
	gcInfo->rowNo = row;
	gcInfo->columnNo = column;
	gcInfo->child =child;

	gridChildren.push_back(gcInfo);
	IBase::AddChild(child);

	return true;

}

bool Grid::Render(){
	glColor3f(0.1f,0.2f,0.0f);


	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();


	glColor3f(1.0f,0.0f,0.5f);

	float posX = pos.x -0.5f*size.x;
	float posY = pos.y -0.5f*size.y;
	glBegin(GL_LINES);
		glVertex2f(posX,posY);
		glVertex2f(posX, posY+size.y);
	glEnd();

	for(int i=0;i<totalColumn;i++){
		printf("Redering column at %f\n",posX);
		posX += columnInfo.at(i)->absSize;
		glBegin(GL_LINES);
			glVertex2f(posX,posY);
			glVertex2f(posX, posY+size.y);
		glEnd();
	}


	posX = pos.x -0.5f*size.x;
	glBegin(GL_LINES);
		glVertex2f(posX,posY);
		glVertex2f(posX+ size.x, posY);
	glEnd();

	for(int i=0;i<totalRow;i++){
		printf("Redering row at %f\n",posY);
		posY += (rowInfo.at(i))->absSize;
		glBegin(GL_LINES);
			glVertex2f(posX,posY);
			glVertex2f(posX+ size.x, posY);
		glEnd();
	}


	int totalChildren = gridChildren.size();
	for(int i=0;i<totalChildren;i++){
		GridChildInfo* gcInfo = gridChildren.at(i);
		gcInfo->child->Render();


	}

	return true;

}
