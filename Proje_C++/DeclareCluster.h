#ifndef DECLARECLUSTER_H
#define DECLARECLUSTER_H

#include "DataOfFile.h"	  // Include the header file for DataOfFile class
#include <cmath>
#include <map>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;

// Define a multimap type with string keys and pairs of int and pair of doubles

typedef multimap<string, pair<int, pair<double, double>>> ClustersMap;

// Forward declarations
class DataOfFile;

// Class definition for DeclareCluster
class DeclareCluster
{

    friend void findCluster(DataOfFile &, DeclareCluster &);
    friend void doIteration(DataOfFile &, DeclareCluster &);

public:
    // Constructor with default values for number of clusters, number of iterations, and initial coordinates
    DeclareCluster(const int &noc = 1, const int &noi = 100, const double &xcoor = 0.0, const double &ycoor = 0.0);

    // Destructor for DeclareCluster class
    ~DeclareCluster();

    // Getter functions
    int getNumberOfCluster() const;
    int getNumberOfIteration() const;

    // Function to calculate the length between two points
    double calculateLenght(double x1, double y1, double x2, double y2) const;

    // Function to split points to clusters based on the closest cluster center
    void splitToPoints(map < int,pair<double,double>, less <int >>::const_iterator, int *);

    // Function to edit the center coordinates of clusters based on the points assigned to them
    void EditCenterOfClusters();

    // Function to set the initial coordinates for the clusters
    void setCoordinate(double, double);
	
    // Function to print the clusters
    void printClusters() const;


private:
    double xCoordinate;          // Initial x-coordinate for clusters
    double yCoordinate;          // Initial y-coordinate for clusters
    int numberOfcluster;         // Number of clusters
    int numberOfIteration;       // Number of iterations
    pair<double, double> *centerOfClusters; // Array to store the center coordinates of clusters
    ClustersMap *k_mean;          // Multimap to store clusters
};

#endif
