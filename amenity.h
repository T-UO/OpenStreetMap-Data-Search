
/*amenity.h*/

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

#pragma once

#include <string>
#include <vector>
#include <utility>

#include "nodes.h"

using namespace std;


/**
  * @brief defines an amenity in the open street map.
  *
  * Defines an amenity with an open street map id, the type
  * of amenity (e.g. "fast_food"), a name (e.g. "Panera Bread"), 
  * a street address (e.g. "1700 Sherman Ave"), and the IDs of
  * the nodes that define the position / outline of the amenity.
  */
class Amenity
{
private:
  long long ID;
  string    Name;
  string    StreetAddress;
  string    AmenityType;
  vector<long long> NodeIDs;

public:
  // constructor
  Amenity(long long id, string name, string streetAddr, string amenityType);

  // adds the given nodeid to the end of the vector
  void add(long long nodeid);

  // prints amenity information to the console
  void print();  // summary
  void print(Nodes& nodes);
  
  // getters:
  long long getID();
  string    getName();
  string    getStreetAddress();
  string    getAmenityType();
  vector<long long> getNodeIDs(); // returns a sorted copy of the node ids
  pair<double, double> getLocation(Nodes& nodes);
};
