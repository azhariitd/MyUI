#include "Grid.h"
#include "MouseEvent.h"
#include "PlotScroll.h"
#include "Plot.h"
class PlotWrap:public Grid{

private:
	float3 color;
	Plot* plot;
public:
	void SetColor(float3 color_);
	virtual bool Render();
	

	MouseEvent mouseEvent;

	virtual bool OnMouseDown(int button, float2& pos);
	virtual bool OnMouseUp(int button, float2& pos);
	

	
	PlotWrap();
	bool OnHorizontalScrollChange(PlotScrollEventArgs &arg);
};
