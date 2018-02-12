/*******************************************************************/
/*	Object Oriented Programming							           */
/*	Fall 2015									                   */
/*	Homework # 2									               */
/*  															   */
/*	                                                               */
/*  CELAL TEMİZ                                                    */
/* 	101044070											           */
/*																   */
/*	                                                               */
/*  A global C function that returns the array index of the first  */ 
/*  mode element of a given array.                                 */ 
/*******************************************************************/
#include<iostream>

using namespace std;


// DayOfYear Data Type 
class DayOfYear
{
	public:
		
			// Constructors
			DayOfYear(int monthvalue,int dayvalue);
			DayOfYear(int monthvalue);
			DayOfYear();
			
			// Getters 
			int getMonth();
			int getDay();
			
			// Setters
			void setMonth(int monthvalue);
			void setDay(int dayvalue);
	private:
			
			// Private Members
			int month;
			int day;
};


// Person Data Type 
class Person
{

	public:

			// Constructors
			Person(int weightValue,int heightValue);
			Person(int weightValue);
			Person();

			// Getters 

			int getWeight();
			int getHeight();
			
			// Setters 
			void setWeight(int weightValue);
			void setHeight(int heightValue);
	private:
			
			// Private Members 
			int weight;
			int height;
};


// Equals Functions 
int intEquals(const void* previous, const void *next);
int doubleEquals(const void* previous, const void *next);
int charEquals(const void* previous, const void *next);
int DayOfYearEquals(const void* previous, const void *next);
int PersonEquals(const void* previous, const void *next);



int return_mode(const void * base, size_t num, size_t size, bool (* equals) (const void *, const void *));


int main()
{

    int i,j,k=1,m=0,n,p,r,repetitionIndex[10];
    
    int maxRepNumber;
    
    // Sample Arrays 
         
    int    intTYPE[10] = {1,3,3,1,4,5,3,1,7,3};  
    double doubleTYPE[10] = {1.1,3.3,3.3,1.2,4.5,5.7,3.3,1.9,8.7,6.3}; 
    char   charTYPE[10] = {'a','b','c','c','e','f','b', 'c', 'e', 'f'}; 
    
    DayOfYear oneDay[10];
	Person onePerson[10];	

	oneDay[0]=DayOfYear(2,16);	
	oneDay[1]=DayOfYear(4, 5);
	oneDay[2]=DayOfYear(10,21);
	oneDay[3]=DayOfYear(1,10);
	oneDay[4]=DayOfYear(2,16);
	oneDay[5]=DayOfYear(2,16);	
	oneDay[6]=DayOfYear(3, 5);
	oneDay[7]=DayOfYear(8, 4);
	oneDay[8]=DayOfYear(1,23);
	oneDay[9]=DayOfYear(2,16);

	
	onePerson[0] = Person(80,180);
	onePerson[1] = Person(62,160);	
	onePerson[2] = Person(60,183);
	onePerson[3] = Person(80,180);
	onePerson[4] = Person(99,192);
	onePerson[5] = Person(70,160);
	onePerson[6] = Person(75,170);	
	onePerson[7] = Person(80,180);
	onePerson[8] = Person(80,180);
	onePerson[9] = Person(99,192);   
	
     
    int repetitionNumber = 0 ;
          
        for(i=0; i<9; i++) {
            for(j=i+1; j<10; j++){
                if(intTYPE[i] == intTYPE[j])
                repetitionNumber++;                   
            }                       
        repetitionIndex[k] = repetitionNumber;
        k++;
        repetitionNumber = 1;
        }

        maxRepNumber = repetitionIndex[1];
        p=1; 
        
        // Repetition Number 
        for(i=2; i<=10; i++)
        {
            if(maxRepNumber <  repetitionIndex[i]) {
                maxRepNumber = repetitionIndex[i];
                p=i;
               }
        }
        
        cout << endl;
               
        cout  << "Your values are : ";
        for(int z=0; z<10; ++z) {
            cout << intTYPE[z] << " "; 
        }         
        cout << endl << endl;
        
            
        for (int s=0; s<10; ++s) {      
           if (intTYPE[p] == intTYPE[s] ) {             
           cout <<"First Index : "  << s << endl;
           break;         
           }
       }
        
        cout <<"Mode Element  : "     << intTYPE[p] << endl;
        cout <<"Repetition Number : " << repetitionIndex[p] << endl << endl;
    
    
        /*
	
	    cout<<"\nDay of Year type test result -> ";
		cout<< ((return_mode((DayOfYear*)oneDay,10,sizeof(DayOfYear),DayOfYearEquals)).getMonth()<<endl;

		cout<<"Integer type test result -> ";
		cout<<(return_mode((int*)intTYPE,10,sizeof(int),intEquals))<<endl;	

		cout<<"Person type  test test result -> ";
		cout<<(return_mode((Person*)onePerson,10,sizeof(Person),PersonEquals)).getWeight()<<endl;	
		
		cout<<"Double type test test result -> ";
		cout<<(return_mode((double*)doubleTYPE,10,sizeof(double),doubleEquals))<<endl;

		cout<<"Char  type test result -> "; 
		cout<<(return_mode((char*)charTYPE,5,sizeof(char),charComparing))<<endl;
	
	    */
       
 
    return 0;
}


	
// Integer Numbers Equal
int intComparing(const void *previous, const void *next)
{

	return ((*(int*)next) - (*(int*)previous));
}

// Double Numbers Equal
int doubleComparing(const void*previous,const void *next)
{	
	return  ((*(double*)next) - (*(double*)previous));
}

// Character Equal 
int charComparing(const void*previous,const void *next)
{
	return ((*(char*)next) - (*(char*)previous));
}

// DayofYear Equal 
int DayOfYearComparing(const void*previous,const void *next)
{
	DayOfYear p = *(DayOfYear*)previous;
	DayOfYear n = *(DayOfYear*)next;

	if(p.getMonth()>n.getMonth()) return -1;
	else if(p.getMonth()<n.getMonth()) return 1;
	else 
		{	
			if(p.getDay()>n.getDay()) return -1;
			else if(p.getDay()<n.getDay()) return 1;
			else  return 0;
		}

}

// Person Equal 
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

// Initialize to values
DayOfYear::DayOfYear(int monthvalue,int dayvalue):month(monthvalue),day(dayvalue)
{
}

DayOfYear::DayOfYear(int monthvalue):month(monthvalue),day(1)
{
}

DayOfYear::DayOfYear():month(1),day(1)
{
}

// Getter Function,return private member 
int DayOfYear::getMonth()
{
	return month;
}

int DayOfYear::getDay()
{
	return day;
}

// Setter function, assignment private member 
void DayOfYear::setDay(int dayvalue)
{
	day=dayvalue;
}

void DayOfYear::setMonth(int monthvalue)
{
	month=monthvalue;
}

// Initialize to values
Person::Person(int weightValue,int heightValue):weight(weightValue),height(heightValue)
{
}

Person::Person(int weightValue):weight(weightValue),height(1)
{
}
Person::Person():weight(1),height(1)
{
}

// Getter Function,return private member 
int Person::getWeight()
{
	return weight;
}

int Person::getHeight()
{
	return height;
}

// Setter function, assignment private member 
void Person::setHeight(int heightValue)
{
	height=heightValue;
}

void Person::setWeight(int weightValue)
{
	weight=weightValue;
}

// The returned value should be array index of the mode element of the array

int return_mode (const void * base, size_t num, size_t size, bool (* equals) (const void *, const void *))
{

	// Code here

}

