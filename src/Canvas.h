#include "IBase.h"
#include "MouseEvent.h"

#define RESWIDTH 10
#define MOVEWIDTH 20

typedef struct ChildData_{
	float2 absPos,relPos;
	float2 size;
	IBase *child;
}ChildData;


typedef enum MouseMoveOp_{
	ResizeLeft=1,
	ResizeRight=2,
	ResizeBotton=4,
	ResizeTop=8,

	Move = 16,
	None = 0,

}MouseMoveOp;

class Canvas:public IBase{




private:

	std::vector<ChildData*> canvasChildren;
	float3 bgColor, fgColor;

	MouseMoveOp mouseOp;
	ChildData* selected;
	
	bool CheckChildrenDown(int button,float2& pos_);
	

public:
	void SetColor(float3 color_);
	virtual bool Render();

	virtual void SetContainingRectangle(float2 &size_, float2& pos_);



	MouseEvent mouseEvent;

	virtual bool OnMouseDown(int button, float2& pos);
	virtual bool OnMouseUp(int button, float2& pos);
	virtual bool OnMouseMove(float2& pos_, float2& delPos, int mouseState);	
	
	virtual bool AddChild(IBase* child);
	bool AddChild(IBase* child, float2& pos, float2& size);
	virtual bool RemoveChild(IBase* child);

	Canvas();	

};
