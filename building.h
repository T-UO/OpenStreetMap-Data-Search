/*building.h*/

/**
  * @brief defines a building in the open street map.
  *
  * Defines a campus building with an open street map id, a 
  * name (e.g. "Mudd"), a street address (e.g. "2233 Tech Dr"), 
  * and the IDs of the nodes that define the position / outline 
  * of the building.
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
  * @brief defines a building in the open street map.
  *
  * Defines a campus building with an open street map id, a 
  * name (e.g. "Mudd"), a street address (e.g. "2233 Tech Dr"), 
  * and the IDs of the nodes that define the position / outline 
  * of the building.
  */
class Building
{
private:
  long long ID;
  string    Name;
  string    StreetAddress;
  vector<long long> NodeIDs;

public:
  // constructor
  Building(long long id, string name, string streetAddr);

  // adds the given nodeid to the end of the vector
  void add(long long nodeid);

  // prints building information to the console
  void print();  // summary
  void print(Nodes& nodes);  // detailed
  
  // getters:
  long long getID();
  string    getName();
  string    getStreetAddress();
  vector<long long> getNodeIDs();  // returns a sorted copy of the node ids
  pair<double, double> getLocation(Nodes& nodes);

};

