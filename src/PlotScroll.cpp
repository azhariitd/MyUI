#include "PlotScroll.h"

#include<stdio.h>


PlotScroll::PlotScroll(Orientation orientation_){
	SetColor(float3(RandFloat(),RandFloat(),RandFloat()));
	orientation = orientation_;
	
	SetVerticalAllignment(Stretch);
	SetHorizontalAllignment(Stretch);

	clickedState = None;

	scale = 1.20f;
	offset = 1.0f;
	UpdatePos();
}

void PlotScroll::SetColor(float3 color_){

	//color = color_;
}

void PlotScroll::OnScrollScale(float del, bool lowEnd){

	if(orientation == Vertical){
		printf("Scaling\n");
		if(lowEnd){
			scrollSize.y -= del;
			scrollPos.y  += 0.5f*del;
			
			float maxSizeY = -pos.y + 0.5f*size.y+scrollPos.y;
			if(scrollSize.y*0.5f >  maxSizeY || scrollSize.y < 10.0f){
				scrollSize.y +=del;
				scrollPos.y -= 0.5f*del;
			}else{
				scale = scrollSize.y/size.y;
				float ymin = pos.y - 0.5f*size.y + 0.5f*scrollSize.y;
				offset = (scrollPos.y - ymin)/(size.y - scrollSize.y);				
			
			}

		}else{
			scrollSize.y += del;
			scrollPos.y  += 0.5f*del;
			
			float maxSizeY = pos.y + 0.5f*size.y-scrollPos.y;
			if(scrollSize.y*0.5f >  maxSizeY || scrollSize.y < 10.0f){
				scrollSize.y -=del;
				scrollPos.y -= 0.5f*del;
			}else{
				
				scale = scrollSize.y/size.y;
				float ymin = pos.y - 0.5f*size.y + 0.5f*scrollSize.y;
				offset = (scrollPos.y - ymin)/(size.y - scrollSize.y);				
			
			}




		}


	}else if(orientation == Horizontal){
		printf("Scaling\n");
		if(lowEnd){
			scrollSize.x -= del;
			scrollPos.x  += 0.5f*del;
			
			float maxSizeX = -pos.x + 0.5f*size.x+scrollPos.x;
			printf("fvalues are %f %f\n",maxSizeX,scrollSize.x*0.5f);
			if(scrollSize.x*0.5f >  maxSizeX || scrollSize.x < 10.0f){
				scrollSize.x +=del;
				scrollPos.x -= 0.5f*del;
			}else{
				scale = size.x/scrollSize.x;
				float xmin = pos.x - 0.5f*size.x + 0.5f*scrollSize.x;
				offset = (scrollPos.x - xmin)/(size.x - scrollSize.x);				
			
			}

		}else{
			scrollSize.x += del;
			scrollPos.x  += 0.5f*del;
			
			float maxSizeX = pos.x + 0.5f*size.x-scrollPos.x;
			if(scrollSize.x*0.5f >  maxSizeX || scrollSize.x <10.0f){
				scrollSize.x -=del;
				scrollPos.x -= 0.5f*del;
			}else{
				
				scale = size.x/scrollSize.x;
				float xmin = pos.x - 0.5f*size.x + 0.5f*scrollSize.x;
				offset = (scrollPos.x - xmin)/(size.x - scrollSize.x);				
			
			}




		}


	}
	printf("Calling evenn");
	PlotScrollEventArgs arg;
	arg.offset = offset;
	arg.scale = scale;
	plotScrollEvent(arg);
}

void PlotScroll::OnScrollMove(float del){
	
	if(orientation==Vertical){
		float ymin = pos.y-0.5f*size.y + 0.5f*scrollSize.y;
		float ymax = pos.y+0.5f*size.y - 0.5f*scrollSize.y;
		scrollPos.y += del;
		if(scrollPos.y < ymin || scrollPos.y> ymax){
			scrollPos.y -=del;
		}else{
			offset = (scrollPos.y-ymin)/(ymax-ymin);

		}

	}else if(orientation == Horizontal){
		float xmin = pos.x-0.5f*size.x + 0.5f*scrollSize.x;
		float xmax = pos.x+0.5f*size.x - 0.5f*scrollSize.x;
		scrollPos.x += del;
		if(scrollPos.x < xmin || scrollPos.x> xmax){
			scrollPos.x -=del;
		}else{
			offset = (scrollPos.x-xmin)/(xmax-xmin);

		}



	}

	printf("Calling scroll event\n");
	PlotScrollEventArgs arg;
	arg.offset = offset;
	arg.scale = scale;
	plotScrollEvent(arg);


}

bool PlotScroll::OnMouseMove(float2 &pos_, float2 &delPos,int mouse){

	if(clickedState == ScaleSmall){
		if(orientation==Vertical){
			OnScrollScale(delPos.y,true);
		}else if(orientation == Horizontal){
			OnScrollScale(delPos.x,true);
		}
	}else if(clickedState == ScaleLarge){
		if(orientation==Vertical){
			OnScrollScale(delPos.y,false);
		}else if(orientation == Horizontal){
			OnScrollScale(delPos.x,false);
		}
	

	}else if(clickedState == Scroll){
		if(orientation==Vertical){
			OnScrollMove(delPos.y);
		}else if(orientation == Horizontal){
			OnScrollMove(delPos.x);
		}
	

	}else{
	}

	glutPostRedisplay();
	
	return false;
}

void PlotScroll::UpdatePos(){
	if(orientation == Vertical){
		//draw rect
		scrollSize = float2(size.x,size.y/scale);
		float ymin = pos.y - 0.5f*size.y + 0.5f*scrollSize.y;
		float ymax = pos.y+ 0.5f*size.y-0.5f*scrollSize.y;
		float ypos = ymin+(ymax-ymin)*offset;
//		scroli	printf("Here\n");
		scrollPos = float2(pos.x, ypos);

	}
	else if(orientation ==Horizontal){

		scrollSize = float2(size.x/scale,size.y);
		float xmin = pos.x - 0.5f*size.x + 0.5f*scrollSize.x;
		float xmay = pos.x+ 0.5f*size.x-0.5f*scrollSize.x;
		float xpos = xmin+(xmay-xmin)*offset;
		scrollPos = float2(xpos,pos.y);


	}



}

void PlotScroll::SetContainingRectangle(float2 &pos_, float2 &size_){
	IBase::SetContainingRectangle(pos_,size_);
	UpdatePos();

}

bool PlotScroll::Render(){

	glColor3fv((float*)(&color));
	glColor3f(1.0f,1.0f,1.0f);	


	glBegin(GL_QUADS);
		glVertex2f(pos.x-size.x/2,pos.y - size.y/2);
		glVertex2f(pos.x-size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y + size.y/2);
		glVertex2f(pos.x+size.x/2,pos.y - size.y/2);

	glEnd();

	glColor3f(1.0f,1.0f,0.0f);
	glBegin(GL_QUADS);
	glVertex2f(scrollPos.x - 0.5f*scrollSize.x,scrollPos.y-0.5f*scrollSize.y);
	glVertex2f(scrollPos.x + 0.5f*scrollSize.x,scrollPos.y-0.5f*scrollSize.y);
	glVertex2f(scrollPos.x + 0.5f*scrollSize.x,scrollPos.y+0.5f*scrollSize.y);
	glVertex2f(scrollPos.x - 0.5f*scrollSize.x,scrollPos.y+0.5f*scrollSize.y);
	glEnd();


	return true;
}

bool PlotScroll::OnMouseDown (int button, float2& pos_){
	
	float xDif = pos_.x -scrollPos.x ;
	float yDif = pos_.y -scrollPos.y;
	printf("Scroll clicked\n");


	if(xDif<scrollSize.x*0.5f && xDif > -scrollSize.x*0.5f && yDif < scrollSize.y*0.5f && yDif > -scrollSize.y*0.5f){
		
		if(orientation == Vertical){
			if(yDif > 0.4f*scrollSize.y){
				clickedState = ScaleLarge;
			}else if(yDif < -0.4f*scrollSize.y){
				clickedState = ScaleSmall;
			}else{
				clickedState = Scroll;
			}
		}else if(orientation ==  Horizontal){
			if(xDif > 0.4f*scrollSize.x){
				clickedState = ScaleLarge;
			}else if(xDif < -0.4f*scrollSize.x){
				clickedState = ScaleSmall;
			}else{
				clickedState = Scroll;
			}
		}
		printf("Clicked state is %d\n",clickedState);
		glutPostRedisplay();

		return true;
	}

	return false;
}

bool PlotScroll::OnMouseUp (int button, float2& pos_){

	float xDif = pos.x -pos_.x + 0.5f*size.x;
	float yDif = pos.y -pos_.y + 0.5f*size.y;

	clickedState = None;

	if(xDif>0.0 && xDif< size.x && yDif>0.0f && yDif < size.y){
		MouseEventArg me;
		me.button = LeftButton;
		me.state = Released;
		mouseEvent(me);

		return true;
	}else{
		return false;
	}


}


