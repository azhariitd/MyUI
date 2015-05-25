#include "IBase.h"
#include "MouseEvent.h"

class Plot:public IBase{

private:
	float3 color;
	double PlotFunc(double x);
	double minX, maxX;
	double minY, maxY;
	float offset,scale,prevScale;
	GLuint vboId;

public:
	void SetColor(float3 color_);
	virtual bool Render();
	

	MouseEvent mouseEvent;

	virtual bool OnMouseDown(int button, float2& pos);
	virtual bool OnMouseUp(int button, float2& pos);
	
	Plot();
	void SetValues(float offset_, float scale_);
};
