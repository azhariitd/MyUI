#include "IBase.h"
#include "MouseEvent.h"

class Rect:public IBase{

private:
	float3 color;

public:
	void SetColor(float3 color_);
	virtual bool Render();

	MouseEvent mouseEvent;

	virtual bool OnMouseDown(int button, float2& pos);
	virtual bool OnMouseUp(int button, float2& pos);
	

};
