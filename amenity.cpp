/*amenity.cpp*/

/**
  * @brief defines an amenity in the open street map.
  *
  * Defines an amenity with an open street map id, the type
  * of amenity (e.g. "fast_food"), a name (e.g. "Panera Bread"), 
  * a street address (e.g. "1700 Sherman Ave"), and the IDs of
  * the nodes that define the position / outline of the amenity.
  *
  * @note Written by Prof. Joe Hummel
  * @note Northwestern University
  */

#include <iostream>
#include <algorithm>
#include <iomanip>

#include "amenity.h"

using namespace std;


//
// constructor
//
Amenity::Amenity(long long id, string name, string streetAddr, string amenityType)
  : ID(id), Name(name), StreetAddress(streetAddr), AmenityType(amenityType)
{
  // vector is default initialized by its constructor
}


//
// adds the given nodeid to the end of the vector.
//
void Amenity::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}


//
// prints information about this amenity to the console
//
void Amenity::print()  // summary
{
  //
  // print a simple one line summary of amenity:
  //
  cout << this->Name << " (" << this->AmenityType << "): "
       << this->StreetAddress
       << endl;
       
  return;
}

/**
 * @brief Prints detailed information about this amenity.
 *
 * Outputs the amenity's name, type, and street address, followed by
 * its latitude and longitude obtained from the provided Nodes object.
 *
 * @param nodes reference to the Nodes collection used to look up coordinates
 * @return nothing
 */
void Amenity::print(Nodes& nodes)  // detailed
{
  //
  // print a more complete, detailed output of amenity:
  //
  cout << this->Name << " (" << this->AmenityType << ")" << endl;
  cout << " OSM ID: " << this->ID << endl;
  cout << " Address: " << this->StreetAddress << endl;
  
  //
  // implement getLocation() function, call here, and output
  // returned latitude and longitude:
  //

  // saves current formatting
std::ios oldState(nullptr);
oldState.copyfmt(cout);

  pair<double,double> location = this->getLocation(nodes);
  // cout << fixed << setprecision(4)
  //      << " GPS Location: " << location.first << ", " << location.second << endl;
  cout << " GPS Location: " << location.first << ", " << location.second << endl;
  cout.copyfmt(oldState); // end of debugging purposes - removes trailing 0s

  //
  // loop through the sorted nodeids, and for each id, call
  // the find( ) function in the Nodes class to obtain
  // latitude, longitude, and whether it's an entrance or not.
  //
  // If the find( ) function returns false, output "**NODE NOT FOUND**"
  //
  // output format:
  //   id: (latitude, longitude)
  // or
  //   id: (latitude, longitude), is entrance
  // where each line has 2 leading spaces
  //
  cout << " Nodes:" << endl;   
  vector<long long> sorted = this->getNodeIDs();
  

  // look up its coordinates and entrance flag;
  // if found, prints (lat, lon) and ", is entrance" when applicable
  for (long long item : sorted)
  {
    double lat = 0.0;
    double lon = 0.0;
    bool isEntrance = false;
    
    if (nodes.find(item, lat, lon, isEntrance)) {
      cout << "  " << item << ": (" << lat << ", " << lon << ")"
           << (isEntrance ? ", is entrance" : "")
           << endl;
    }
    else {
      cout << " " << item << ": <node not found>\n";
    }
  }
  
  return;
}


//
// getters:
//
long long Amenity::getID() 
{ return this->ID; }

string Amenity::getName()
{ return this->Name; }

// vector<Amenity>& getAmenities() 
// { return osmAmenities; }

string Amenity::getStreetAddress()
{ return this->StreetAddress; }

string Amenity::getAmenityType()
{ return this->AmenityType; }

// returns a sorted copy of the node ids
vector<long long> Amenity::getNodeIDs()
{ 
  vector<long long> copy = this->NodeIDs;
  std::sort(copy.begin(), copy.end());
  return copy;
}


// Calcs Amenity's location by averaging it's lat/lon of its
// referenced nodes
pair<double, double> Amenity::getLocation(Nodes& nodes)
{
  // collects sorted nodes IDs
  vector<long long> items = this->getNodeIDs();
  if (items.empty())
    return make_pair(0.0, 0.0);

  double latTot = 0.0;
  double lonTot = 0.0;
  int count = 0;

  // sums coordinates
  for (long long id : items)
  {
    double lat = 0.0, lon = 0.0;
    bool isEntrance = false;
    if (nodes.find(id, lat, lon, isEntrance)) {
      latTot += lat;
      lonTot += lon;
      count++;
    }
  }

  // if nothing found
  if (count == 0)
    return make_pair(0.0, 0.0);

  double avgLat = latTot / count;
  double avgLon = lonTot / count;
  return make_pair(avgLat, avgLon);
}