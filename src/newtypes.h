#ifndef NEWTYPES_HEADER

#define NEWTYPES_HEADER

typedef struct float2_{
	union{
		float x,r;
	};
	union{
		float y,g;
	};

	struct float2_& operator =(const struct float2_& a)
	{
		x = a.x;
	        y = a.y;
		return *this;
	}

	float2_(float x_, float y_){
		x= x_;
		y=y_;
	}

	float2_(){
		x=y=0;
	}
}float2;



typedef struct float3_{
		
	union {
		float x,r;
	};

	union{
		float y,g;
	};

	union{
		float b,z;
	};
	


	struct float3_& operator =(const struct float3_& a)
	{
		x = a.x;
	        y = a.y;
		z = a.z;
		return *this;
	}

	float3_(float x_, float y_,float z_){
		x= x_;
		y=y_;
		z = z_;
	}

	float3_(){
		x=y=z=0;
	}

}float3;



#endif
