#include "newtypes.h"
#include <map>
#include <vector>
#include <stdlib.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>



#ifndef IBASE_HEADER

#define IBASE_HEADER

using namespace std;

typedef enum Allignment_{
	Top = 0,
	Left =0,
	Center=1,
	Right=2,
	Bottom=2,
	Stretch=3,

}Allignment;


class IBase{

//#Region Metrics
	protected:
		float2 pos, size, absSize, maxSize;
		Allignment horAlignment, verAlignment;

	public:
		virtual void SetContainingRectangle(float2& size_, float2& pos_) ;
		void SetHorizontalAllignment(Allignment allignment) ;
		void SetVerticalAllignment(Allignment allignment);


//#Region userdata
	private:
		map<int,void*>  userDataMap;
	public:
		bool AddUserData(int key, void *data);
		bool DeleteUserData(int key);
		void *GetUserData(int key);;


//#Region Children
	protected:
		vector<IBase*> children;
		IBase *parent;

	public:
		bool AddChild(IBase* child);
		bool RemoveChild(IBase* child);
		void SetParent(IBase* parent_);
		
//#Region Render
	public:
		virtual bool Render();

		/*
//#Region input handlers
	public:
		bool OnKeyPressed(Key key, int keyState);
		bool OnMouseMoved(float2& pos, float2& delPos, int mouse, int keyState);
		bool OnMouseDown(float2& pos);
		bool OnMouseUp(float2& pos);
*/

		IBase();
};

#endif
