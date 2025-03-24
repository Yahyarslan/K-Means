#include <iostream>
#include "DataOfFile.h"
#include "DeclareCluster.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
	DataOfFile a;
	cout << a;
	
	int numcluster;
	int numiteration;
	
	
	cout << "\nPlease enter the cluster number: ";
	cin >> numcluster;
	cout << "Please enter the iteration number: ";
	cin >> numiteration;
	cout << endl;

	DeclareCluster b(numcluster,numiteration);
	doIteration(a,b);
	b.printClusters();
	return 0;
}