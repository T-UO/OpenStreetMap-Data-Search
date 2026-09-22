/*dist.h*/

/**
  * @brief computes the distance between 2 GPS coordinates.
  *
  * Computes the distance between 2 position, given in
  * (latitude, longitude) coordinates.
  *
  * @note Written by Prof. Joe Hummel
  * @note Northwestern University
  */

#pragma once


/**
  * @brief computes the distance between 2 GPS coordinates.
  *
  * Returns the distance in miles between 2 points (lat1, long1) and 
  * (lat2, long2). Latitudes are positive above the equator and 
  * negative below; longitudes are positive heading east of Greenwich 
  * and negative heading west. Example: Chicago is (41.88, -87.63).
  *
  * @param lat1 Latitude of first coordinate
  * @param lon1 Longitude of first coordinate
  * @param lat2 Latitude of second coordinate
  * @param lon2 Longitude of second coordinate
  * @return distance in miles
  * @note Reference: chatGPT using haversine formula
  */
double distBetween2Points(double lat1, double lon1, double lat2, double lon2);

