#include "IBase.h"
#include "MouseEvent.h"

typedef enum SlOrientation_{
	SlVertical,
	SlHorizontal
}SlOrientation;

#define HANDLEWIDTH 32
#define HANDLEHEIGHT 16

class Slider:public IBase{

private:
	float3 bgColor, fgColor;
	float valNormalized;
	SlOrientation orientation;
public:
	void SetColor(float3 color_);
	virtual bool Render();

	MouseEvent mouseEvent;

	virtual bool OnMouseDown(int button, float2& pos);
	virtual bool OnMouseUp(int button, float2& pos);
	

	Slider();
};
