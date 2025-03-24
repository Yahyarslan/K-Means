#include "DeclareCluster.h"

// Constructor for DeclareCluster class
DeclareCluster::DeclareCluster(const int &noc, const int &noi, const double &xcoor, const double &ycoor)
    : numberOfcluster(noc), numberOfIteration(noi), xCoordinate(xcoor), yCoordinate(ycoor)
{

    centerOfClusters = new pair<double, double>[getNumberOfCluster()];
    k_mean = new ClustersMap[getNumberOfCluster()];

    // Initialize centerOfClusters with random coordinates within a range
    for (int i = 0; i < getNumberOfCluster(); i++)
    {
        pair<double, double> c(rand() % 80000, rand() % 80000);
        centerOfClusters[i] = c;
    }
}

// Function to set the initial coordinates for the clusters
void DeclareCluster::setCoordinate(double xcoor, double ycoor)
{
    xCoordinate = xcoor;
    yCoordinate = ycoor;
}

// Getter function for the number of clusters
int DeclareCluster::getNumberOfCluster() const
{
    return numberOfcluster;
}

// Getter function for the number of iterations
int DeclareCluster::getNumberOfIteration() const
{
    return numberOfIteration;
}

// Function to calculate the Euclidean distance between two points
double DeclareCluster::calculateLenght(double x1, double y1, double x2, double y2) const
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

// Function to assign a point to the nearest cluster in the multimap
void DeclareCluster::splitToPoints(map < int,pair<double,double>, less <int >>::const_iterator i, int *index)
{
    pair<double, double> coor(i->second.first, i->second.second);

    string indexString = to_string(*index + 1);

    // Construct the key for the multimap using make_pair
    string clusterKey = "CLUSTER " + indexString;

    // Use emplace to insert the pair into the multimap
    k_mean[*index].emplace(clusterKey, make_pair(i->first, coor));
}

// Function to update the center coordinates of clusters based on assigned points
void DeclareCluster::EditCenterOfClusters()
{
    for (int i = 0; i < getNumberOfCluster(); ++i)
    {
        // Calculate the sum of X and Y coordinates using accumulate
        double sumX = accumulate(k_mean[i].begin(), k_mean[i].end(), 0.0, [](double sum, const auto &element)
                                 { return sum + element.second.second.first; });

        double sumY = accumulate(k_mean[i].begin(), k_mean[i].end(), 0.0, [](double sum, const auto &element)
                                 { return sum + element.second.second.second; });

        // Calculate the average X and Y coordinates
        double newCenterX = sumX / k_mean[i].size();
        double newCenterY = sumY / k_mean[i].size();

        // Update the centerOfClusters array
        pair<double, double> a(newCenterX, newCenterY);
        centerOfClusters[i] = a;
    }
}

// Function to find the nearest cluster for each point in the DataOfFile
void findCluster(DataOfFile &kc, DeclareCluster &dc)
{
    const int SIZE = dc.getNumberOfCluster();

    for (auto it = kc.pairs.begin(); it != kc.pairs.end(); it++)
    {
        // Initialize minClusterIndex to the first element
        auto minClusterIndex = dc.centerOfClusters;

        // Initialize minDistance to the distance from the first cluster
        double minDistance = dc.calculateLenght(minClusterIndex->first, minClusterIndex->second, it->second.first, it->second.second);

        // Iterate through the remaining clusters to find the one with minimum distance
        for (auto clusterIt = dc.centerOfClusters + 1; clusterIt != dc.centerOfClusters + SIZE; ++clusterIt)
        {
            double distance = dc.calculateLenght(clusterIt->first, clusterIt->second, it->second.first, it->second.second);

            if (distance < minDistance)
            {
                minDistance = distance;
                minClusterIndex = clusterIt;
            }
        }

        // Assign the current sample to the nearest cluster
        int index = static_cast<double>(distance(dc.centerOfClusters, minClusterIndex));
        dc.splitToPoints(it, &index);
    }

    // Update the center coordinates of clusters
    dc.EditCenterOfClusters();

    // dc.printClusters(); // Uncomment if needed
}

// Function to perform multiple iterations of finding clusters
void doIteration(DataOfFile &c, DeclareCluster &d)
{
    for (int i = 0; i < d.getNumberOfIteration(); i++)
    {
        for (int j = 0; j < d.getNumberOfCluster(); j++)
            d.k_mean[j].clear();

        findCluster(c, d);
    }
}

// Function to print clusters
void DeclareCluster::printClusters() const 
{
  		cout<<"CLUSTER Name"<<"\t"<<"INDEX"<<"\t"<<"X\t"<<"\t"<<"Y"<<endl;
		for_each(k_mean, k_mean + getNumberOfCluster(), [](const auto &cluster) {
        	for_each(cluster.begin(), cluster.end(), [](const auto &point) {
            	cout << point.first << "\t" <<point.second.first<<"\t"<< point.second.second.first << "\t" << point.second.second.second << endl;
        	});
       		cout <<endl<<"****************************************************"<<endl;
    	});
}

//Destructor deallacation
DeclareCluster::~DeclareCluster()
{
	delete [] k_mean;
	delete [] centerOfClusters;
}

