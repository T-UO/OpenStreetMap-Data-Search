/*buildings.h*/

/**
  * @brief A collection of buildings in the open street map.
  *
  * @note Written by Prof. Joe Hummel
  * @note Northwestern University
  */

#pragma once

#include <vector>

#include "building.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Amenties;
class Nodes;  // forward declaration

/**
  * @brief A collection of buildings in the open street map.
  */
class Buildings
{
public:
  vector<Building> osmBuildings;

/**
  * @brief constructor to retrieve all the buildings from the open street map.
  *
  * Given an XML document, reads through the document and 
  * stores all the buildings into the vector data member.
  * 
  * @param xmldoc An XML document object denoting the open street map.
  * @return nothing.
  */
  Buildings(XMLDocument& xmldoc);
  
/**
  * @brief prints all the buildings in summary form.
  *
  * @return nothing
  */
  void print_all();


/**
 *  @brief prints Building(s) based off substring
 *
 *  @return nothing
 *
 *
 */
  void subStringPrint(string& name, Nodes& nodes);


  /**
 *  @brief finds nearest fast food
 *
 *  @return nothing
 *
 *
 */
  void findNearestFastFood(string& name, Amenities& amenities, Nodes& nodes);

};


