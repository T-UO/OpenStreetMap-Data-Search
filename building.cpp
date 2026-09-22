/*building.cpp*/

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

#include <iostream>
#include <algorithm>
#include <iomanip>

#include "building.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  // vector is default initialized by its constructor
}


//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}


//
// prints information about this building to the console
//
void Building::print()  // summary
{
  //
  // print a simple one line summary of building:
  //
  cout << this->Name << ": "
       << this->StreetAddress
       << endl;
       
  return;
}

/**
 * @brief Prints detailed information about this building.
 *
 * Displays the building's name and street address, followed by the
 * latitude and longitude of each node t
 *
 * @param nodes reference to the Nodes collection used to look up coordinates
 * @return nothing
 */
void Building::print(Nodes& nodes)  // passes by reference
{
  //
  // print a more complete, detailed output of building:
  //
  cout << this->Name << endl;
  cout << " OSM ID: " << this->ID << endl;
  cout << " Address: " << this->StreetAddress << endl;
  
  //
  // TODO: 
  //
  // implement getLocation() function, call here, and output
  // returned latitude and longitude:
  //

// save current formatting 
std::ios oldState(nullptr);
oldState.copyfmt(cout);

pair<double,double> location = this->getLocation(nodes);
//cout << fixed << setprecision(4) << " GPS Location: " << location.first << ", " << location.second << endl;
cout << " GPS Location: " << location.first << ", " << location.second << endl;

// restore previous formatting - removes trailing 0s
cout.copyfmt(oldState);

  //
  // TODO:
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
  
  for(long long item : sorted){
	double lat = 0.0;
	double lon = 0.0;
	bool isEntrance = false;
	
	if(nodes.find(item, lat, lon, isEntrance)){
		cout << "  " << item << ": (" << lat << ", " << lon << ")"
              << (isEntrance ? ", is entrance" : "")
              << endl;
	}

	else{
		cout << " " << item << ": <node not found>\n";
	}

	}
  
  return;
}




//
// getters:
//
long long Building::getID() 
{ return this->ID; }

string Building::getName()
{ return this->Name; }

string Building::getStreetAddress()
{ return this->StreetAddress; }

// returns a sorted copy of the node ids
vector<long long> Building::getNodeIDs()
{ 
  vector<long long> copy = this->NodeIDs;
  
  std::sort(copy.begin(), copy.end());
  
  return copy;
}

pair<double, double> Building::getLocation(Nodes& nodes)
{
  //
  // TODO
  //
  
  // returns building's stored node IDs 
  vector<long long> items = this->getNodeIDs();

  if(items.empty()){
    return make_pair(0.0, 0.0);
  }

    double latTot = 0.0;
    double lonTot = 0.0;
    bool isEntrance = false;
    int count = 0;

    for(long long item : items){
     double lat = 0.0; 
     double lon = 0.0;
        bool isEntrance = false;
        if(nodes.find(item, lat, lon, isEntrance)){ // accumulates only if node exists
          latTot += lat;
          lonTot += lon;
          count++;
        }
           
    }
        if(count == 0){
          return make_pair(0.0, 0.0);
        }

        double averageLat = latTot / count;
        double averageLon = lonTot / count;
        return make_pair(averageLat, averageLon);

  
    }
	
  


