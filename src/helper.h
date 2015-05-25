

#ifndef HELPER_INC
#define HELPER_INC


int NextPowerOf2(int a){

	a-=1;
	int shift  = 1;
	while ((a+1)&a){
		a |= a >> shift;
		shift <<=1;

	}

	return a+1;
}

#endif
