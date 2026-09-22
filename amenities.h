/* amenities.h */

/**
  * @brief A collection of amenities in the open street map.
  *
  * @note Written by Prof. Joe Hummel
  * @note Northwestern University
  */

#pragma once

#include <vector>
#include <string>

#include "amenity.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Nodes;  // forward declaration

/**
  * @brief A collection of amenities in the open street map.
  */
class Amenities
{
public:
  // all amenity objects
  vector<Amenity> osmAmenities;

  // all amenity types (e.g., "cafe", "fast_food"); may contain duplicates
  vector<string> amenityTypes;

/**
  * @brief constructor to retrieve all the amenities from the open street map.
  *
  * Given an XML document, reads through the document and
  * stores all the amenities into the vector data members.
  *
  * @param xmldoc An XML document object denoting the open street map.
  * @return nothing.
  */
  Amenities(XMLDocument& xmldoc);

/**
  * @brief prints all amenities in summary form (name + address).
  *
  * @return nothing
  */
  void print_all();

/**
 * @brief prints amenity types, 5 per line with a space after each.
 *
 * @return nothing
 */
  void print_5();

/**
 * @brief prints Amenity(ies) whose type/name contains the given substring,
 *        case-insensitive. Uses Nodes to resolve coordinates for detailed print.
 *
 * @return nothing
 */
  void subStringPrint(string& type, Nodes& nodes);
};