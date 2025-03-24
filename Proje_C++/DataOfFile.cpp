#include "DataOfFile.h"	// Include the header file for DataOfFile class


#include <iomanip>      // For formatted output
#include <fstream>      // For file input/output

int DataOfFile::index = 0;  // Initialize static index variable

// Function to get the next available index and increment it
int DataOfFile::getIndex()
{
    return index++;
}

// Constructor for DataOfFile class, calls setSamples to initialize the cluster
DataOfFile::DataOfFile()
{
    setSamples();
}

// Overloaded stream insertion operator for printing DataOfFile objects
ostream &operator<<(ostream &output, const DataOfFile &cluster)
{
    // Print header for the output table
    output << setw(6) << "INDEX" << setw(15) << "X" << setw(15) << "Y" << endl;

    // Iterate over the samples in the cluster and print each entry
    for (const auto &sample : cluster.getSamples())
    {
        output << setw(6) << sample.first << fixed << setprecision(6) << setw(15) << sample.second.first
               << setw(15) << sample.second.second << endl;
    }

    return output;
}

// Set the x-coordinate for a given subscript in the cluster
void DataOfFile::setX(int subscript, double x_coor)
{
    // Check if the subscript is within the valid range [0-40)
    if (subscript >= 0 && subscript < 40)
    {
        // Iterate over the pairs in the cluster and set the x-coordinate
        for(data::iterator it = pairs.begin(); it != pairs.end(); ++it)
            it->second.first = x_coor;
    }
    else
        throw invalid_argument("Subscript must be [0-40)");
}

// Set the y-coordinate for a given subscript in the cluster
void DataOfFile::setY(int subscript, double y_coor)
{
    // Check if the subscript is within the valid range [0-40)
    if (subscript >= 0 && subscript < 40)
    {
        // Iterate over the pairs in the cluster and set the y-coordinate
        for(data::iterator it = pairs.begin(); it != pairs.end(); ++it)
            it->second.second = y_coor;
    }
    else
        throw invalid_argument("Subscript must be [0-40)");
}

// Set both x and y coordinates for a given subscript in the cluster
void DataOfFile::setCoordinates(int subscript, double x_value, double y_value)
{
    // Check if the subscript is within the valid range [0-40)
    if (subscript >= 0 && subscript < 40)
    {
        // Set the x and y coordinates using the corresponding functions
        setX(subscript, x_value);
        setY(subscript, y_value);
    }
    else
        throw invalid_argument("Subscript must be [0-40)");
}

// Get the x-coordinate for a given subscript in the cluster
double DataOfFile::getX(int subscript) const
{
    auto it = pairs.find(subscript);  // Use 'auto' to deduce the correct type

    // Check if the subscript is valid
    if (it != pairs.end()) {
        return it->second.first;  // Return the x-coordinate
    } 
    else {
        throw out_of_range("Subscript not found in DataOfFile::getX");  // Handle error: subscript not found
    }
}

// Get the y-coordinate for a given subscript in the cluster
double DataOfFile::getY(int subscript) const
{
    auto it = pairs.find(subscript);  // Use 'auto' to deduce the correct type

    // Check if the subscript is valid
    if (it != pairs.end()) {
        return it->second.second;  // Return the y-coordinate
    } 
    else {
        throw out_of_range("Subscript not found in DataOfFile::getY");  // Handle error: subscript not found
    }
}

// Get the samples (pairs) in the cluster
data DataOfFile::getSamples() const
{
    return pairs;
}

// Read samples from a file and populate the cluster's pairs
void DataOfFile::setSamples()
{
    ifstream input("40.txt");  // Open the input file

    if (!input.is_open())
    {
        cerr << "Error opening file!" << endl;  // Print an error message if file opening fails
    }
    else
    {
        double value1 = 0;
        double value2 = 0;

        // Read values from the file and insert them into the cluster's pairs
        while (input >> value1 >> value2)
        {
            pairs.insert(data::value_type(DataOfFile::getIndex(), make_pair(value1, value2)));
        }

        input.close();  // Close the input file
    }
}

// Destructor for DataOfFile class
DataOfFile::~DataOfFile()
{
    // Empty Destructor
}
