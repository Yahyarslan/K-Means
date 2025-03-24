#ifndef DATAOFFILE_H
#define DATAOFFILE_H
#include<iostream>
// This program includes necessary C++ libraries
#include <string>       // For handling strings
#include <algorithm>    // For algorithms like sort
#include <map>          // For using the map container
#include <stdexcept>    // For standard exceptions
#include <cstdlib>      // For general-purpose functions
#include <array>        // For using arrays
#include <ctime>        // For working with time
#include <utility>      // For using pair
//#include "DeclareCluster.h" // Include user-defined header file

using namespace std;

typedef map < int,pair<double,double>, less <int >> data;

class DeclareCluster;

class DataOfFile
{
	friend void findCluster(DataOfFile &, DeclareCluster &);
	friend void doIteration(DataOfFile &, DeclareCluster &);
	
	friend ostream &operator<<(ostream &, const DataOfFile &);
	
	public:
		DataOfFile();
		
		//setters
		void setSamples();
		void setX(int,double);
		void setY(int,double);
		void setCoordinates(int, double, double);
		
		/// Getters
		double getX(int) const;
		double getY(int) const;
		data getSamples() const;
		static int getIndex();
		 
		
		~DataOfFile();
		
		
		
	private:
		
		static int index ;
		
		data pairs;	
};

#endif