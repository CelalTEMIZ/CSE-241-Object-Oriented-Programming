/*******************************************************************/
/*	Object Oriented Programming							           */
/*	Fall 2014									                   */
/*	Homework # 3									               */
/*  															   */
/*	                                                               */
/*  CELAL TEMİZ                                                    */
/* 	101044070											           */
/*																   */
/*	                                                               */
/* Class name is Vect3D.This class represent a three dimensional   */
/* vector with X, Y, and Z components such as a  = (1.2, 3.1, 4.0) */
/* Calculate the dot product, magnitude and vector product between */
/* two vector 													   */
/*******************************************************************/


/* İnclude Libraries */

#include<iostream>
#include<cstdlib>
#include<cmath>


using namespace std;


/* Class Vect3D */
class Vect3D
{	

	/* Member functions and constructors */

	public:

		Vect3D();
		Vect3D(double xCoordinate);
		Vect3D(double xCoordinate, double yCoordinate);
		Vect3D(double xCoordinate, double yCoordinate, double zCoordinate);


		/* Setter */
		void set(double newX, double newY, double newZ);

		/* Getter */
		double getX() const;
		double getY() const;
		double getZ() const;

		/* Input and Output Function */
		void input();
		void output() const;

	
		/* Calculate Functions */
		double magnitudeVector3D() const;	 
		double dotProductVector3D(Vect3D &otherVector);
		Vect3D vectorProduct3D(Vect3D otherVector);

		void testFunction();

	/* Private data members */

	private:

		double x;
		double y;
		double z;
		
};



int main()
{

	/* Test object to member function testing */

	Vect3D vector;

	vector.testFunction();
	
	

	return 0;



}


/* Setter to x,y,z values */
void Vect3D::set(double newX, double newY, double newZ)
{

		x = newX;
		
		y = newY;

		z = newZ;


}

/* Getter to x value */
double Vect3D::getX() const
{

	return x;
}

/* Getter to y value */
double Vect3D::getY() const
{

	return y;
}

/* Getter to z value */
double Vect3D::getZ() const
{

	return z;
}	

/* Input Function to vector parameter */
void Vect3D::input()
{

	cout<<"Enter the vector parameters like x y z " <<endl;

	cin>> x >> y >> z;

}	

/* No parameter constructor (X, Y, and Z are all zero) */
Vect3D::Vect3D()
{
	x = 0.0;
	
	y = 0.0;

	z = 0.0;

}

// One parameter constructor that set X component 
// and set the other components to zero 

Vect3D::Vect3D(double xCoordinate)
{

	x = xCoordinate;	

	y = 0.0;

	z = 0.0;
}

// Two parameter constructor that set X and Y components 
// and set the Z component to zero 

Vect3D::Vect3D(double xCoordinate, double yCoordinate)
{
	x = xCoordinate;
	
	y = yCoordinate;

	z = 0.0;
}

//  Three parameter constructor

Vect3D::Vect3D(double xCoordinate, double yCoordinate, double zCoordinate)
{
	x = xCoordinate;

	y = yCoordinate;

	z = zCoordinate;

}

// Display vector values */
void Vect3D::output() const
{

	
	cout << "(" << x << ","<< y << ","<< z << ")";
	cout <<endl;

}

// Function that returns the magnitute of the Vect3D

double Vect3D::magnitudeVector3D() const
{

	return sqrt(x*x + y*y + z*z);

}


// Function that takes another Vect3D object as parameter
// and returns the result of dot product (a double) 
// between this object and the parameter

double Vect3D::dotProductVector3D(Vect3D &otherVector)
{
	

	return x*otherVector.x + y*otherVector.y + z*otherVector.z;

}

// Function that takes another Vect3D object as parameter 
// and returns the result of vectoR product ( a Vect3D) 
// between this object and the parameter

Vect3D Vect3D::vectorProduct3D(Vect3D otherVector)
{

	Vect3D result (y*otherVector.z-z*otherVector.y, z*otherVector.x-x*otherVector.z, x*otherVector.y-y*otherVector.x);

	result.output();

	return result;
}


// Test function to all members
void Vect3D::testFunction()
{

	/* Sample objects */

	Vect3D v0,v5;
	Vect3D v1(4,3,7),v2(2,5,4);
	Vect3D v3(1.2,2.5,3.8),v4(7.4,9.1,4.8);

	// User input test
	cout << "\n 		TEST RESULTS\n";	
	v0.input();
	cout << "Your vector is " ;
	v0.output();


	v4.output();

	// Getters testing
	cout << v3.getX() << endl;
	cout << v4.getY() << endl;
	cout << v2.getZ() << endl;

	// Function call by value 
	v1.vectorProduct3D(v2);
	v3.vectorProduct3D(v4);
	

	cout << v0.magnitudeVector3D() << endl;
	cout << v2.magnitudeVector3D() << endl;
	cout << v3.magnitudeVector3D() << endl;

	// Function call by reference 
	cout << v1.dotProductVector3D(v2) << endl;
	cout << v3.dotProductVector3D(v4) << endl;
	
	
	

}



