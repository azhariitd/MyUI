#include "IBase.h"
#include "MouseEvent.h"
#include <math.h>

#define PI 3.14159265



class GraphDisplay:public IBase{

private:
	float3 bgColor,axisColor,fgColor;

	GLuint vertexBufferId;
	int plotVertexSize;
	float xAxisOffset;
	float yAxisOffset;

public:
	GraphDisplay();
	void SetColor(float3 color_);

	virtual bool Render();

	MouseEvent mouseEvent;

	virtual bool OnMouseDown(int button, float2& pos);
	virtual bool OnMouseUp(int button, float2& pos);


	void SetData(float* dataArray,int arraySize, float xMin, float xMax, float yMin, float yMax);	

};
