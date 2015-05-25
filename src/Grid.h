#include "IBase.h"
#include <vector>

#ifndef GRID_INCLUDE
#define GRID_INCLUDE

typedef enum SizeType_{
	Absulute,
	Relative,

}SizeType;

typedef struct RowInfo_{
	SizeType sizeType;
	float size;

	float absSize;
	float pos;

}RowInfo;

typedef struct GridChildInfo_{
	int rowNo, columnNo;
	IBase* child;

}GridChildInfo;

class Grid: public IBase{

private:
	void UpdateChildenMetrics();

	std::vector<RowInfo*> rowInfo;
	std::vector<RowInfo*> columnInfo;
	
	std::vector<GridChildInfo*> gridChildren;
	
	int totalRow, totalColumn;

public:
	virtual void SetContainingRectangle(float2& size, float2& pos) ;	


	void AddRowDefinition(SizeType sizeType_, float size);
	void AddColumnDefinition(SizeType sizeType_, float size);

	bool AddChild(int row, int column, IBase* child);

	Grid();

	virtual bool Render();	

};

#endif
