#include "Del.h"
#include <stdio.h>


class MyClass{

	public:
		void PrintInt(int a){
			printf("Called class %d \n",a*a);
		}

};

void Print(int a){
	printf("Called from global %d\n",a);
}

int main(){

	MyClass mc;
	Event<void, int>  e;

	Event<void, int>::S* e1 = new Event<void,int>::S(&Print);
	e +=e1; 
	e += new Event<void,int>::T<MyClass>(&mc,&MyClass::PrintInt);
	e(23);

	e-=e1;
	e(22);

}
