#include "IBase.h"

#ifndef STACKPANEL_INCLUDE
#define STACKPANEL_INCLUDE

typedef enum Orientation_{
	Vertical,
	Horizontal,

}Orientation;

class StackPanel: public IBase{

private:
	Orientation orientation;
	void UpdateChildenMetrics();

public:
	virtual void SetContainingRectangle(float2& size, float2& pos) ;	

	void SetOrientation(Orientation orientation_);

	StackPanel();

	virtual bool Render();	

};

#endif
