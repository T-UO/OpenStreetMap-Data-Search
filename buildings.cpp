/*buildings.cpp*/

/**
  * @brief A collection of buildings in the open street map.
  *
  * @note Written by Prof. Joe Hummel
  * @note Northwestern University
  */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cctype>


#include "dist.h"
#include "amenities.h"
#include "buildings.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Nodes;
static string lower_copy(string s);
static string sort_key(string s);

/**
  * @brief constructor to retrieve all the buildings from the open street map.
  *
  * Given an XML document, reads through the document and 
  * stores all the buildings into the vector data member.
  * 
  * @param xmldoc An XML document object denoting the open street map.
  * @return nothing.
  */
Buildings::Buildings(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document element by element, 
  // looking for amenities:
  //
  XMLElement* element = osm->FirstChildElement();

  while (element != nullptr)
  {
    string tag = element->Value();
    
    if (tag != "node" && tag != "way") {
      element = element->NextSiblingElement();
      continue;
    }
    
    const XMLAttribute* attr = element->FindAttribute("id");
    assert(attr != nullptr);
    
    //
    // if this is a building, store info into vector:
    //
    if (osmContainsKeyValue(element, "building", "university"))
    {
      string name = osmGetKeyValue(element, "name");
      
      if (name == "") { // no name, ignore!
        element = element->NextSiblingElement();
        continue;
      }

      string streetAddr = osmGetKeyValue(element, "addr:housenumber")
        + " "
        + osmGetKeyValue(element, "addr:street");

      //
      // create building object, then add the associated
      // node ids to the object:
      //
      // The node/way id serves as the amenity id:
      //
      long long id = attr->Int64Value();

      Building B(id, name, streetAddr);
      
      if (tag == "node") {
        //
        // this node defines the position of the building, so
        // add to vector of node references as our only ref:
        //
        B.add(id);
      }
      else {
        assert(tag == "way");
        
        //
        // the way has a list of nodes that define the perimeter,
        // so collect the node ids as references to the perimeter
        // nodes:
        //
        XMLElement* nd = element->FirstChildElement("nd");
        
        while (nd != nullptr)
        {
          const XMLAttribute* ndref = nd->FindAttribute("ref");
          assert(ndref != nullptr);

          long long id = ndref->Int64Value();

          B.add(id);

          // advance to next node ref:
          nd = nd->NextSiblingElement("nd");
        }
      }//else

      //
      // add the building to the vector:
      //
      this->osmBuildings.push_back(B);
    }//if

    element = element->NextSiblingElement();
  }//while
  
  //
  // we have all the buildings, sort by name:
  //
  
  //
  // TODO: sort the vector of buildings
  //
	sort(this->osmBuildings.begin(), this->osmBuildings.end(),
          [](Building& a, Building& b){
              return a.getName() < b.getName();
          }); 
  //
  // done:
  //
  return;
}



/**
 * @brief Returns a lowercase copy of the input string.
 *
 *
 * @param s the input string to be converted
 * @return a lowercase version of the input string
 */
static string lower_copy(string s) {
  transform(s.begin(), s.end(), s.begin(),
            [](unsigned char c){ return (char)tolower(c); });
  return s;
}



/**
  * @brief prints all the buildings in summary form.
  *
  * @return nothing
  */
void Buildings::print_all()
{
  for (Building B : this->osmBuildings) {
    B.print();
  }
  
  return;
}


/**
 *  @brief prints building(s) based off substring
 *
 *  @param name substring to search for within building names
 *. @param nodes reference to the Nodes collection used for coordinate lookup
 *  @return nothing
 */

void Buildings:: subStringPrint(string& name, Nodes& nodes){
  bool anyFound = false;
	string query = name;
	for(size_t i = 0; i < query.size(); i++){
		char c = query[i];
		query[i] = (char)tolower(c);
	} // converts substring into chars

	for(Building b: this->osmBuildings){
		if(b.getName() == name){
			b.print();
      anyFound = true;
			continue; // accounts for multiple buildings that contain substring
		}
		 // building names case-insensitive
		string text = b.getName();
		for(size_t i = 0; i < text.size(); i++){
			char c = text[i];
			text[i] = (char)tolower(c); //converts building name to chars
		}

		if(!query.empty()){
			size_t pos = text.find(query);
			if(pos < text.size()){
				// b.print(Nodes(xmldoc)); // passed in by reference
        b.print(nodes);
        anyFound = true;
			}
		}

	}
  if (!anyFound && !query.empty()) {
        cout << "No such building" << endl;
    }
}

void Buildings::findNearestFastFood(string& name, Amenities& amenities, Nodes& nodes)
{
  // normalizes query for case-insensitive comparison
  string query = lower_copy(name);
  bool anyMatched = false; // tracks if *any* building matched the query

  // scans building for queries
  for (Building& building : this->osmBuildings)
  {
    string buildingName = lower_copy(building.getName());
    if (buildingName.find(query) >= buildingName.size()){
      continue;
    }

    anyMatched = true; // building match

    // compute building location
    pair<double,double> buildingLoc = building.getLocation(nodes);
    double buildingLat = buildingLoc.first;
    double buildingLon = buildingLoc.second;

    double bestDistance = 9999999; // unlikely to exceed - sentinel value
    Amenity* nearestAmenity = 0;

    for (Amenity& amenity : amenities.osmAmenities)
    {
      if (amenity.getAmenityType() != "fast_food"){
        continue;
      }

      pair<double,double> amenityLoc = amenity.getLocation(nodes);
      double amenityLat = amenityLoc.first;
      double amenityLon = amenityLoc.second;

      double distance = distBetween2Points(buildingLat, buildingLon, amenityLat, amenityLon);
      if (distance < bestDistance) {
        bestDistance = distance;
        nearestAmenity = &amenity;
      }
    }

    // outputs
    cout << building.getName() << endl;

    if (nearestAmenity)
      cout << nearestAmenity->getName() << " (fast_food): "
           << nearestAmenity->getStreetAddress() << endl
           << " Distance: " << bestDistance << " miles" << endl;
    else
      cout << "No fast food found." << endl;
  }
    if (!anyMatched && !query.empty()) {
    cout << "No such building" << endl;
  }
  }

  
