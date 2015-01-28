#include "IBase.h"


class Rect:public IBase{

private:
	float3 color;

public:
	void SetColor(float3 color_);
	virtual bool Render();


};
