#include<vector>





template<typename RetType, typename ArgType>
class Event{
	
	private:
			class Base{
		public:
			virtual ~Base(){ }
			virtual RetType operator()(ArgType) = 0;

		};

		std::vector<Base*> mPtrs;




	public:


		class S:public Base
		{
			typedef RetType (*Func)(ArgType);
			
			private:
				Func mFunc;

			public:
				S(Func aFunc):mFunc(aFunc){};
				
				virtual RetType operator()(ArgType a){
					return mFunc(a);
				}
		};

		
		template< typename Class>
		class T : public Base
		{

			typedef RetType (Class::*Func) (ArgType );
			private:
				Class* mThis;
				Func  mFunc;

			public:
			T(Class* aThis, Func aFunc):mThis(aThis), mFunc(aFunc){}
			virtual RetType operator()(ArgType a){
				return (mThis->*mFunc)(a);
			}
		};





		Event& operator+=(Base* aPtr){
			mPtrs.push_back(aPtr);
			return *this;
		}

		Event& operator-=(Base* aPtr){
			typename std::vector<Base*>::iterator iter = mPtrs.begin();
			typename std::vector<Base*>::iterator end = mPtrs.end();

			for(;iter!=end;iter++){
				if(*iter == aPtr){
					mPtrs.erase(iter);
					return *this;
				}

			}


		}


		RetType operator()(ArgType a)
		{
			typename std::vector<Base*>::iterator end = mPtrs.end();
			RetType rt;
			for(typename std::vector<Base*>::iterator i = mPtrs.begin(); i!=end;i++)
			{
				rt = 	(**i)(a);
			}

			return rt;
		}


};

