#include "IBase.h"
#include "MouseEvent.h"
#include "Event.h"

#ifndef PLOTSCROLL_INCLUDE_
#define PLOTSCROLL_INCLUDE_

typedef enum Orientation_{
	Vertical, Horizontal
}Orientation;

typedef struct PlotScrollEventArgs_{
	float offset;
	float scale;

}PlotScrollEventArgs;


typedef Event<bool, PlotScrollEventArgs&> PlotScrollEvent; 

class PlotScroll:public IBase{



private:
	typedef enum ClickedState_{
		None,ScaleSmall,ScaleLarge,Scroll
	}ClickedState;

	ClickedState clickedState;

static	const float buttonSize = 20.0f;
	float3 color;
	Orientation orientation;
	float scale;
	float offset;

	float2 scrollPos,scrollSize;
	float2 btn1Pos,btn1Size,btn2Pos, btn2Size;
	void UpdatePos();
	void OnScrollMove(float del);
	void OnScrollScale(float del, bool lowEnd);
public:
	void SetColor(float3 color_);
	virtual void SetContainingRectangle(float2 &size, float2 &pos);
	virtual bool Render();
	

	MouseEvent mouseEvent;
	PlotScrollEvent plotScrollEvent;

	virtual bool OnMouseDown(int button, float2& pos);
	virtual bool OnMouseUp(int button, float2& pos);
	virtual bool OnMouseMove(float2 &pos, float2 &delPos, int mouse); 

	PlotScroll(Orientation orientation);
};


#endif
