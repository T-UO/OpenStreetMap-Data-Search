/*main.cpp*/

/**
  * @brief Program for working with open street map of NU Evanston campus.
  *
  * Program to input Nodes (positions), Buildings and Amenities 
  * from an Open Street Map file. User can search for buildings
  * and nearby amenities.
  *
  * @note Written by Tagbo Ugo-Obi
  * @note Starter code by Prof. Joe Hummel
  * @note Northwestern University
  */

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "amenity.h"
#include "amenities.h"
#include "buildings.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"

using namespace std;


/**
  * @brief main program
  *
  * @return 0 denoting success
  */
int main()
{
  XMLDocument xmldoc;
  
  cout << "** NU open street map **" << endl;
  cout << endl;
  
  string filename = "nu.osm";

  //
  // 1. load XML-based map file 
  //
  if (!osmLoadMapFile(filename, xmldoc))
  {
    // error message already output by function
    return 0;
  }
  
  //
  // 2. create and read the nodes, which are the various known 
  //    positions on the map:
  //
  Nodes nodes(xmldoc);

  //
  // 3. create and read the university buildings:
  //
  Buildings buildings(xmldoc);
  
  //
  // 4. create and read the amenities:
  //
  //
      Amenities amenities(xmldoc);
  //

  //
  // 5. stats
  //
  cout << "# of nodes:     " << nodes.getNumOsmNodes() << endl;
  cout << "# of buildings: " << buildings.osmBuildings.size() << endl;
  cout << "# of amenity types: " << amenities.amenityTypes.size() << endl;
  cout << "# of amenities:     " << amenities.osmAmenities.size() << endl; 

  //
  // 6. Now let the user search for buildings and amenities:
  //
  while (true)
  {
    string cmd;

    cout << endl;
    cout << "Enter cmd (b, a, f) or $ to end>" << endl;

    cin >> cmd;

    if (cmd == "$") {
      break;
    }
    // enter for building
    else if (cmd == "b") {
      //
      // b ENTER => just list all the buildings
      // b building_name ENTER => search for buildings containing that name
      //
      string name;	
      getline(cin, name);  // read rest of line in case multiple words in building name
      
      //
      // TODO: name WILL contain leading whitespace, remove from string.
      //   
      // HINT: use isspace(c) to see if c is whitespace, and if so, remove
      // from string using s.erase(0, 1) --- remove 1 char at position 0.
      //
      while(!name.empty() && isspace(name.front())){
	      name.erase(0,1);
      }

      buildings.subStringPrint(name, nodes);
      
      if (name == "") {
        // 
        // just list all the buildings in summary mode:
        //
        buildings.print_all();
      }
      else {
        // 
        // find every building that contains this name, use 
        // a case-insensitive search and print a detailed output:
        //
        
        
      }
      
    }
    // enter for amenity
    else if (cmd == "a") {
 
  string amenityType;
  getline(cin, amenityType);  

  // trims leading spaces
  while (!amenityType.empty() && isspace((amenityType.front()))) {
    amenityType.erase(0, 1);
  }

  if (amenityType.empty()) {
    
    amenities.print_5();
  } else {
    // case-insensitive substring search - amenity type
    string query = amenityType;
    for (char& c : query) c = tolower(c);

    bool any = false;
    for (Amenity& A : amenities.osmAmenities) {
      string t = A.getAmenityType();
      for (char& c : t) c = tolower(c);

    size_t pos = t.find(query);
    if (pos < t.size()) {          // found
      A.print(nodes);
      any = true;
    }

    }
    if (!any) {
      cout << "No such amenity" << endl;
    }
  }
}

    else if (cmd == "f") {
    cin.ignore();  // clears leftover newline

    string buildingName;
    getline(cin, buildingName);

    // trim leading whitespace manually, same as your "b" and "a" commands
    while (!buildingName.empty() && isspace(buildingName.front()))
      buildingName.erase(0, 1);

    buildings.findNearestFastFood(buildingName, amenities, nodes);
    }


    else {
      cout << "Unknown command, please try again" << endl; 
    }

  }//while


  //
  // done:
  //
  cout << endl;
  cout << "** Done **" << endl;
  
  // cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
  // cout << "# of Nodes created: " << Node::getCreated() << endl;
  // cout << "# of Nodes copied: " << Node::getCopied() << endl;

  // cout << "# of amenity types: " << amenities.amenityTypes.size() << endl;
  // cout << "# of amenities: "      << amenities.osmAmenities.size() << endl;

  return 0;
}
