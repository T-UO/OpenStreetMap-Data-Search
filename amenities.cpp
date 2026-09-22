/*amenities.cpp*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

#include "amenities.h"
#include "osm.h"

using namespace std;
using namespace tinyxml2;

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

Amenities::Amenities(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  XMLElement* element = osm->FirstChildElement();

  while (element != nullptr)
  {
    string tag = element->Value();

    if (tag != "node" && tag != "way") {
      element = element->NextSiblingElement();
      continue;
    }

    // counts named + unamed amenities
    string amenity_type = osmGetKeyValue(element, "amenity");
    if (amenity_type == "") {
      element = element->NextSiblingElement();
      continue;
    }
    this->amenityTypes.push_back(amenity_type);

    const XMLAttribute* attr = element->FindAttribute("id");
    assert(attr != nullptr);

    string name = osmGetKeyValue(element, "name");

  if (name == "") {
  this->amenityTypes.push_back(amenity_type);  // <-- add this line
  element = element->NextSiblingElement();
  continue;
}

    string streetAddr = osmGetKeyValue(element, "addr:housenumber") + string(" ") + osmGetKeyValue(element, "addr:street");

    long long id = attr->Int64Value();

    Amenity A(id, name, streetAddr, amenity_type);

    if (tag == "node") {
      A.add(id);
    }
    else {
      XMLElement* nd = element->FirstChildElement("nd");
      while (nd != nullptr)
      {
        const XMLAttribute* ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);
        long long nid = ndref->Int64Value();
        A.add(nid);
        nd = nd->NextSiblingElement("nd");
      }
    }

    this->osmAmenities.push_back(A);
    this->amenityTypes.push_back(amenity_type);

    element = element->NextSiblingElement();
  }

  // sort amenities by name (case-insensitive):
  sort(osmAmenities.begin(), osmAmenities.end(),
       [](Amenity& a, Amenity& b){
         string A = lower_copy(a.getName());
         string B = lower_copy(b.getName());
         return A < B;
       });

  // eliminates duplicates from the vector of amenity types to obtain the 32 distinct types
  sort(amenityTypes.begin(), amenityTypes.end());
  amenityTypes.erase(unique(amenityTypes.begin(), amenityTypes.end()),
                     amenityTypes.end());
}

// prints distinct amenity types
void Amenities::print_5()
{
  int cnt = 0;
  for (const string& t : amenityTypes) {
    cout << t << ' ';
    cnt++;
    if (cnt == 5) { cout << endl; cnt = 0; }
  }
  if (cnt != 0) cout << endl;
}

// dragged from Lab02
void Amenities::subStringPrint(string& type, Nodes& nodes)
{
  string q = lower_copy(type);
  bool any = false;

  for (Amenity& a : this->osmAmenities)
  {
    string t = lower_copy(a.getAmenityType());
    if (!q.empty() && t.find(q) != string::npos) {
      a.print(nodes);
      any = true;
    }
  }

  if (!any && !q.empty())
    cout << "No such amenity" << endl;
}