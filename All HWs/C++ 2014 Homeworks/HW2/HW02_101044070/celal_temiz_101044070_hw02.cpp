/*******************************************************************/
/*	Object Oriented Programming							           */
/*	Fall 2014									                   */
/*	Homework # 2									               */
/*  															   */
/*	                                                               */
/*  CELAL TEMİZ                                                    */
/* 	101044070											           */
/*																   */
/*	                                                               */
/* A global C function that returns a pointer to the nth element   */
/* of a given array												   */
/* The returned element should be the nth element of the sorted    */
/* array, so you should sort the array if it is                    */
/* not sorted.                                                     */
/*******************************************************************/


/* Include Library */


#include<iostream>
#include<cstdlib>

using namespace std;


/* DayOfYear Data Type */
class DayOfYear
{
	public:
		
			/* Constructors*/
			DayOfYear(int monthvalue,int dayvalue);
			DayOfYear(int monthvalue);
			DayOfYear();
			
			/* Getters */
			int getMonth();
			int getDay();
			
			/* Setters */
			void setMonth(int monthvalue);
			void setDay(int dayvalue);
	private:
			
			/* Private Members */
			int month;
			int day;
};


/* Person Data Type */
class Person
{

	public:

			/* Constructors*/
			Person(int weightValue,int heightValue);
			Person(int weightValue);
			Person();

			/* Getters */

			int getWeight();
			int getHeight();
			
			/* Setters */
			void setWeight(int weightValue);
			void setHeight(int heightValue);
	private:
			
			/* Private Members */
			int weight;
			int height;
};

/* Function Prototypes */
void * return_nth (const void * base,size_t numOfElements, size_t size,int nth,int (* comparator) (const void *, const void *));

/* Comparator Functions */
int intComparing(const void *previous,const void *next);
int doubleComparing(const void*previous,const void *next);
int charComparing(const void*previous,const void *next);
int DayOfYearComparing(const void*previous,const void *next);
int PersonComparing(const void*previous,const void *next);
void sorting(char *myArray,size_t size,size_t numOfElements,int (* comparator) (const void *, const void *));

int main()
{
		
		/* Sample Arrays */

		int intNumbers[5]={8,4,6,5,9};
		double doubleNumbers[5] = {1.2,3.2,2.4,5.1,4.7};
		char arr[5]={'a','c','b','d','e'};

		DayOfYear oneDay[5];
		Person onePerson[5];	

		oneDay[0]=DayOfYear(2,16);	
		oneDay[1]=DayOfYear(4,5);
		oneDay[2]=DayOfYear(10,21);
		oneDay[3]=DayOfYear(1,10);
		oneDay[4]=DayOfYear(8,7);

		
		onePerson[0] = Person(70,167);
		onePerson[1] = Person(62,160);	
		onePerson[2] = Person(60,183);
		onePerson[3] = Person(80,180);
		onePerson[4] = Person(99,192);
			
			

		/* To display the test results */

		cout<<"\nDay of Year type test result -> ";
		cout<<(*(DayOfYear*)return_nth((DayOfYear*)oneDay,5,sizeof(DayOfYear),3,DayOfYearComparing)).getMonth()<<endl;

		cout<<"Integer type test result -> ";
		cout<<(*(int*)return_nth((int*)intNumbers,5,sizeof(int),2,intComparing))<<endl;	

		cout<<"Person type  test test result -> ";
		cout<<(*(Person*)return_nth((Person*)onePerson,5,sizeof(Person),1,PersonComparing)).getWeight()<<endl;	
		
		cout<<"Double type test test result -> ";
		cout<<(*(double*)return_nth((double*)doubleNumbers,5,sizeof(double),4,doubleComparing))<<endl;

		cout<<"Day of Year type test result -> ";
		cout<<(*(DayOfYear*)return_nth((DayOfYear*)oneDay,5,sizeof(DayOfYear),5,DayOfYearComparing)).getMonth()<<endl;

		/* cout<<"Char  type test result -> "; */
		/* cout<<(*(char*)return_nth((char*)arr,5,sizeof(char),3,charComparing))<<endl;	*/

		cout<<endl;


		return 0;

}

/* The returned element should be the nth element of the sorted array */
void * return_nth (const void * base,size_t numOfElements, size_t size,int nth,int (* comparator) (const void *, const void *))
{

	/* Integer Sort */
	if(size == sizeof(int))
	{
		int *a;
		sorting((char*)base,size,numOfElements,comparator);
		a = (int*)base;
		return (a+nth-1);	
	}

	/* Char sort */
    if(size == sizeof(char))
	{
		char *b;
		sorting((char*)base,size,numOfElements,comparator);
		b = (char*)base;	
		return (b+nth-1);	
	}
	
	/* Double sort */
	if(size == sizeof(double))
	{
		double *c;
		sorting((char*)base,size,numOfElements,comparator);
		c = (double*)base;
		return (c+nth-1);	
	}

	 /* DayOfYear Sort */
	if(size == sizeof(DayOfYear))	
	{
		DayOfYear *d;
		sorting((char*)base,size,numOfElements,comparator);
		d = (DayOfYear*)base;	
		return (d+nth-1);	
	}	

	/* Person Sort */
	if(size == sizeof(Person))	
	{
		Person *e;
		sorting((char*)base,size,numOfElements,comparator);
		e = (Person*)base;
		
		return (e+nth-1);	
	}	


}

/* Integer Numbers compare */
int intComparing(const void *previous,const void *next)
{

	return ((*(int*)next) - (*(int*)previous));
}

/* Double Numbers compare */
int doubleComparing(const void*previous,const void *next)
{	
	return  ((*(double*)next) - (*(double*)previous));
}

/* Character compare */
int charComparing(const void*previous,const void *next)
{
	return ((*(char*)next) - (*(char*)previous));
}

/* DayofYear Compare */
int DayOfYearComparing(const void*previous,const void *next)
{
	DayOfYear p=*(DayOfYear*)previous;
	DayOfYear n=*(DayOfYear*)next;

	if(p.getMonth()>n.getMonth()) return -1;
	else if(p.getMonth()<n.getMonth()) return 1;
	else 
		{	
			if(p.getDay()>n.getDay()) return -1;
			else if(p.getDay()<n.getDay()) return 1;
			else  return 0;
		}

}

/* Person Compare */
int PersonComparing(const void*previous, const void *next)
{
	Person p=*(Person*)previous;
	Person n=*(Person*)next;

	if(p.getWeight()>n.getWeight()) return -1;
	else if(p.getWeight()<n.getWeight()) return 1;
	else 
		{	
			if(p.getHeight()>n.getHeight()) return -1;
			else if(p.getHeight()<n.getHeight()) return 1;
			else  return 0;
		}

}

/* Sorting Function*/
/* Sort the array if it is not sorted.*/
void sorting(char *myArray,size_t size,size_t numOfElements,int (* comparator) (const void *, const void *))
{
	char temp;
	char *a1;
	char *a2;
		

	for(int i=1; i<numOfElements; ++i)
	{
		for(int j=0; j<numOfElements; ++j)
		{

			a1 = myArray + j*size;
			a2 = myArray + (j+1)*size;

					if(comparator(myArray+j*size, myArray+(j+1)*size) < 0)	
					{
						temp = *a1;
						*a1 = *a2;
						*a2 = temp;		
			
					}
		}
	}
}

/* Initialize to values*/
DayOfYear::DayOfYear(int monthvalue,int dayvalue):month(monthvalue),day(dayvalue)
{
}

DayOfYear::DayOfYear(int monthvalue):month(monthvalue),day(1)
{
}

DayOfYear::DayOfYear():month(1),day(1)
{
}

/* Getter Function,return private member */
int DayOfYear::getMonth()
{
	return month;
}

int DayOfYear::getDay()
{
	return day;
}

/* SEtter function, assignment private member */
void DayOfYear::setDay(int dayvalue)
{
	day=dayvalue;
}

void DayOfYear::setMonth(int monthvalue)
{
	month=monthvalue;
}

/* Initialize to values*/
Person::Person(int weightValue,int heightValue):weight(weightValue),height(heightValue)
{
}

Person::Person(int weightValue):weight(weightValue),height(1)
{
}
Person::Person():weight(1),height(1)
{
}

/* Getter Function,return private member */
int Person::getWeight()
{
	return weight;
}

int Person::getHeight()
{
	return height;
}

/* SEtter function, assignment private member */
void Person::setHeight(int heightValue)
{
	height=heightValue;
}

void Person::setWeight(int weightValue)
{
	weight=weightValue;
}










