#include "IBase.h"
#include "MouseEvent.h"

class StateButton:public IBase{

private:
	float3 color;
	static GLuint textureId;

	void CreateTexture();
	int state;
	
public:
	void SetColor(float3 color_);
	virtual bool Render();
	

	MouseEvent mouseEvent;

	virtual bool OnMouseDown(int button, float2& pos);
	virtual bool OnMouseUp(int button, float2& pos);
	
	StateButton();
};

