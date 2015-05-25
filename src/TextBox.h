#include "IBase.h"
#include "MouseEvent.h"
#include "FontManager.h"



class TextBox:public IBase{

private:
	float3 color;
	FontInfo *font;
	char text[32];
	float textWidth;
public:
	void SetColor(float3 color_);
	virtual bool Render();
	

	MouseEvent mouseEvent;

	virtual bool OnMouseDown(int button, float2& pos);
	virtual bool OnMouseUp(int button, float2& pos);
	
	TextBox(FontInfo* font_,char* text);
	TextBox(FontInfo* font_);
	void SetText(char* text);
};
