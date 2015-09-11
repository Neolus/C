/*  This file contains the declaration of class PC which is an acronym of Prediction and Correction. 
**  Class  PC includes three methods. They are Adams-Bashforth-Moulton method, Milne-Simpson method and Hamming method.
*/

#ifndef PC_H
#define PC_H

#include <vector>

class PC
{
private:
	std::vector<double> interval; //The integral interval
	double step; 
	int k; //The current point
	double err;
	double small;
	std::vector<double> x; //The vector of abscissas.
	std::vector<double> y; //The vector of ordinates.
	double (*f)(double,double); //Function pointer points to the math differential equation.
public:
	void Adams();  //The Adams-Bashforth-Moulton method
	void Milne();  // The Milne-Simpson method
	void Hamming(); // The  Hamming method
	//constructor
    PC(double (*f1)(double,double),std::vector<double> area,std::vector<double>points,double h);
	friend void print(const PC & pc,std::ofstream &out);

};
void print(const PC & pc,std::ofstream &out); //declaration of a friend function.This function prints abscissas and ordinates into a file.
#endif