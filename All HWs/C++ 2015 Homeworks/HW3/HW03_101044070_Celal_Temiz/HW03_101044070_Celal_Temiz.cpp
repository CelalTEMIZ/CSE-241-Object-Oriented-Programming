/*******************************************************************/
/*	Object Oriented Programming							           */
/*	Fall 2015									                   */
/*	Homework # 3									               */
/*	                                                               */
/*  CELAL TEMİZ                                                    */
/* 	101044070											           */
/*																   */
/* Class name is Triangle.This class can represent a triangle on a */
/* 2D plane with sides of length A, B, C such as                   */ 
/* T =(A=3.0, B=4.0, C=5.0)                                        */
/* Returns the angle of a triangle corner (angleA, angleB, angleC) */
/* Returns true if the triangle is a right angle triangle          */
/* Returns the area of the triangle                                */
/* Returns the perimeter of the triangle                           */
/*******************************************************************/


/* Include Libraries */

#include<iostream>
#include<cstdlib>
#include<cmath>


#define PI 3.14159265358979323846
#define radianToDegree 180/PI

using namespace std;


// Class Triangle
class Triangle
{	

	// Member functions and constructors 

	public:

		Triangle();
		Triangle(double side_A);
		Triangle(double side_A, double side_B);
		Triangle(double side_A, double side_B, double side_C);


		// Setters 
		void setA(double newA);
		void setB(double newB);
		void setC(double newC);
		void setABC(double newA, double newB, double newC);

		// Getter 
		double getA() const;
		double getB() const;
		double getC() const;

		// Input and Output Function 
		void input();
		void output() const;

	
		// Calculate Functions 
		double angleA() const;
		double angleB() const;
		double angleC() const;		
		double trianglePerimeter() const;
		double triangleArea() const;		
		bool   rigthAngleTriangle() const;
		void   testFunction();
        void   testCallByValue(Triangle newTriangle) const;
        void   testCallByReference(Triangle &newTriangle) const;
        
	/* Private data members */

	private:

		double A;
		double B;
		double C;
		void testingOfSides();
};


int main()
{

	// Test object to member function testing

	Triangle vector;

	vector.testFunction();
	
	
	return 0;


}

// Setter to A,B,C values 
void Triangle::setABC(double newA, double newB, double newC)
{
    
    if (newA > 0)
      
		A = newA;
	else
	{	
	    cerr << "Illegal A Value ! Program Aborted. " << endl;
	    exit(1);
	}	
	
	if (newB > 0)
      
		B = newB;
	else
	{	
	    cerr << "Illegal B Value ! Program Aborted. " << endl;
	    exit(1);
	}
	
	if (newC > 0)
      
		C = newC;
	else
	{	
	    cerr << "Illegal B Value ! Program Aborted. " << endl;
	    exit(1);
	}
	
}
// Setter functions
void Triangle::setA(double newA)
{
    A = newA;
}

void Triangle::setB(double newB)
{
    B = newB;
}

void Triangle::setC(double newC)
{
    C = newC;
}
// Getter to A value 
double Triangle::getA() const
{

	return A;
}
// Getter to B value 
double Triangle::getB() const
{

	return B;
}

// Getter to C value 
double Triangle::getC() const
{

	return C;
}	

// Input Function to vector parameter 
void Triangle::input()
{

	cout << "Enter the triangle parameters like A B C > " << endl;
    cin >> A >> B >> C;   
    if (A < 0 ||  A > B+C){
	    cout << "Your input A is invalid or must be smaller than " << B+C << " Enter this value again " << endl;
	    cin >> A;
	}
	 if (B < 0 || B > A+C ) {
	    cout << "Your input B is invalid or must be smaller than " << A+C << " Enter this value again " << endl;
	    cin >> B;
	}
	if (C < 0 || C > A+B) {
	    cout << "Your input C is invalid or must be smaller than " << A+B << " Enter this value again " << endl;
	    cin >> C;
	}	
	  
}	

// No parameter constructor (A, B, and C are all 1.0) 
Triangle::Triangle(): A(1.0), B(1.0), C(1.0)
{
	
}

// One parameter constructor that set A component 

Triangle::Triangle(double side_A): A(side_A)
{

    testingOfSides();

}

// Two parameter constructor that set A and Y components 
// and set the Z component to zero 

Triangle::Triangle(double side_A, double side_B): A(side_A), B(side_B), C(1.0)
{
	

	testingOfSides();
}

//  Three parameter constructor

Triangle::Triangle(double side_A, double side_B, double side_C): A(side_A), B(side_B), C(side_C)
{

}

// Display vector values 
void Triangle::output() const
{

	
	cout << "(" << A << ","<< B << ","<< C << ")";
	cout <<endl;

}

// A function that returns the perimeter of the triangle

double Triangle::trianglePerimeter() const
{
	return getA()+getB()+getC();
}

// A function that returns the area of the triangle
double Triangle::triangleArea() const
{
    double s;

    s = (getA()+getB()+getC())/2;
    
	return sqrt((s*(s-getA())*(s-getB())*(s-getC())));
}

// Function that return the angle of a triangle corner (angleA)

double Triangle::angleA() const
{

    double alpha;  
            
    alpha = acos(((getB()*getB()+getC()*getC()-getA()*getA())/(2*getB()*getC())))*radianToDegree;
         
	return alpha;

}

// Function that return the angle of a triangle corner (angleB)
double Triangle::angleB() const
{

    double beta;
            
    beta = acos(((getA()*getA()+getC()*getC()-getB()*getB())/(2*getA()*getC())))*radianToDegree;
            
	return beta;

}

// Function that return the angle of a triangle corner (angleC)
double Triangle::angleC() const
{

    double theta;
            
    theta = acos(((getA()*getA()+getB()*getB()-getC()*getC())/(2*getA()*getB())))*radianToDegree;
         
	return theta;

}

// Function that returns true if the triangle is a right angle triangle
bool Triangle::rigthAngleTriangle() const
{

    if(getA()*getA() == getB()*getB() + getC()*getC())
    
	    return true;
	    
	else if (getB()*getB() == getA()*getA() + getC()*getC()) 
	
	    return true;
	
	else if (getC()*getC() == getA()*getA() + getB()*getB())
    
        return true;
        
    else
    
        return false;
}


// Test function to all members
void Triangle::testFunction()
{

	// Sample objects 

	Triangle v0,v5;
	

	// User input test
	cout << "\n 		TEST RESULTS\n";	
	v0.input();
	
	cout << "Your triangle side is " ;
	v0.output();

    cout << "Perimeter : " << v0.trianglePerimeter()  << endl;
    cout << "Area      : " << v0.triangleArea() << endl;
    
    cout << "Right Angle Triangle : " << v0.rigthAngleTriangle() << endl;

    cout << "Angle A : " << v0.angleA() << endl;
    cout << "Angle B : " << v0.angleB() << endl;
    cout << "Angle C : " << v0.angleC() << endl;
      
    v5.testCallByValue(v0);
    v5.testCallByReference(v0); 
}
void Triangle::testingOfSides()
{
    if (A < 0 || B < 0 || C < 0 ) {
        cout << "Illegal side value !" << endl;
        exit(1);
    }

}

// Test Function to Call By Value
void Triangle::testCallByValue(Triangle newTriangle) const
{
    cout << "------------------------------" << endl;
    cout << endl << "Call By Value Testing Result :" << endl << endl;
 
    cout << "Angle A : " << newTriangle.angleA() << endl;
    cout << "Angle B : " << newTriangle.angleB() << endl;
    cout << "Angle C : " << newTriangle.angleC() << endl;
    cout << "Triangle Area : " << newTriangle.triangleArea() << endl;
    cout << "Triangle Perimeter : " << newTriangle.trianglePerimeter() << endl;
    cout << "Right Angle Triangle : " << newTriangle.rigthAngleTriangle() << endl << endl;

}

// Test Function to Call By Reference
void Triangle::testCallByReference(Triangle &newTriangle) const
{
	cout << "------------------------------" << endl;
    cout << endl << "Call By Reference Testing Result : " << endl << endl;

    cout << "Angle A : " << newTriangle.angleA() << endl;
    cout << "Angle B : " << newTriangle.angleB() << endl;
    cout << "Angle C : " << newTriangle.angleC() << endl;
    cout << "Triangle Area : " << newTriangle.triangleArea() << endl;
    cout << "Triangle Perimeter : " << newTriangle.trianglePerimeter() << endl;
    cout << "Right Angle Triangle : " << newTriangle.rigthAngleTriangle() << endl << endl;
	

}

