/*nodes.cpp*/

//
// A collection of nodes in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 
// References:
// 
// TinyXML: 
//   files: https://github.com/leethomason/tinyxml2
//   docs:  http://leethomason.github.io/tinyxml2/
// 
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:  
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// constructor
//
// Given an XML document, reads through the document and 
// stores all the nodes into the vector data member. Each
// node is a point on the map, with a unique id along with 
// (lat, lon) position. Some nodes are entrances to buildings,
// which we capture as well.
//
Nodes::Nodes(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document node by node: 
  //
  XMLElement* node = osm->FirstChildElement("node");

  while (node != nullptr)
  {
    const XMLAttribute* attrId = node->FindAttribute("id");
    const XMLAttribute* attrLat = node->FindAttribute("lat");
    const XMLAttribute* attrLon = node->FindAttribute("lon");

    assert(attrId != nullptr);
    assert(attrLat != nullptr);
    assert(attrLon != nullptr);

    long long id = attrId->Int64Value();
    double latitude = attrLat->DoubleValue();
    double longitude = attrLon->DoubleValue();

    //
    // is this node an entrance? Check for a 
    // standard entrance, the main entrance, or
    // one-way entrance.
    //
    bool entrance = false;

    if (osmContainsKeyValue(node, "entrance", "yes") ||
      osmContainsKeyValue(node, "entrance", "main") ||
      osmContainsKeyValue(node, "entrance", "entrance"))
    {
      entrance = true;
    }

    //
    // Add node to vector:
    // 
    // This creates an object then pushes copy into vector:
    //
    Node N(id, latitude, longitude, entrance);
    this->osmNodes.push_back(N);

    //
    // next node element in the XML doc:
    //
    node = node->NextSiblingElement("node");
  }
}

//
// find
// 
// Searches the nodes for the one with the matching ID, returning
// true if found and false if not. If found, a copy of the node 
// is returned via the node parameter, which is passed by reference.
//
bool Nodes::find(long long id, double& lat, double& lon, bool& isEntrance) 
{
int low = 0, high = static_cast<int>(this->osmNodes.size()) - 1;

    while (low <= high) {
        int mid = low + ((high - low) / 2);
        long long nodeid = this->osmNodes[mid].getID();

        if (id == nodeid) {
            lat        = this->osmNodes[mid].getLat();
            lon        = this->osmNodes[mid].getLon();
            isEntrance = this->osmNodes[mid].getIsEntrance();
            return true;
        } else if (id < nodeid) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return false;
}

//
// accessors / getters
//
int Nodes::getNumOsmNodes() {
  return (int) this->osmNodes.size();
}

