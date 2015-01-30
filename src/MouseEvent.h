
#ifndef MouseEventInclude
#define MouseEventInclude

#include "Event.h"

typedef enum Button_{
	LeftButton,
	RightButton,
	MiddleButton,
}Button;

typedef enum State_{
	Pressed,
	Released,
	Clicked,

}State;

typedef struct MouseEvent_{
	Button button;
	State state;

}MouseEventArg ;

typedef Event<bool, MouseEventArg&> MouseEvent; 

#endif
