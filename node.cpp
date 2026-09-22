/*node.cpp*/

//
// A node / position in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#include "node.h"

using namespace std;


//
// constructor
//
Node::Node(long long id, double lat, double lon, bool entrance)
  : ID(id), Lat(lat), Lon(lon), IsEntrance(entrance)
{
  Node::Created++;
}

//
// copy constructor:
//
Node::Node(const Node& other)
{
  this->ID = other.ID;
  this->Lat = other.Lat;
  this->Lon = other.Lon;
  this->IsEntrance = other.IsEntrance;

  Node::Copied++;
}

//
// accessors / getters
//
long long Node::getID() {

  Node::CallsToGetID++;

  return this->ID;
}

double Node::getLat() {
  return this->Lat;
}

double Node::getLon() {
  return this->Lon;
}

bool Node::getIsEntrance() {
  return this->IsEntrance;
}

int Node::getCallsToGetID() {
  return Node::CallsToGetID;
}

int Node::getCreated() {
  return Node::Created;
}

int Node::getCopied() {
  return Node::Copied;
}

