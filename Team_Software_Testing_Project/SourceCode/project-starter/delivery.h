#pragma once
#ifndef DELIVERY_H
#define DELIVERY_H

#define MAX_WEIGHT 1000	// Max. allowed weight (kg)
#define MAX_VOLUME 36	// Max. allowed volume (m^3)
#define MAX_DEST_LEN 4 // Max. length of destination coordinate string input 
#define BOX_SIZE_S 0.25 // Size of small package (kg)
#define BOX_SIZE_M 0.5 // Size of medium package (kg)
#define BOX_SIZE_L 1 // Size of large package (kg)
#define NUM_OF_TRUCKS 3 // Number of trucks
#include "mapping.h"

/**
* A truck of blue, green or yellow route.
* @char routeSymbol - The route the truck runs on
* @int weight - current weight occupied
* @double volume - current volume occupied
* @double minDistance - the shortest distance needed to travel to the destination
* @isReady - flag indicating if the truck is ready for delivery (neither full nor unreachable to destination)
*/
struct Truck {
	char routeSymbol;
	int weight;
	double volume;
	double minDistance;
	int isReady;
};

/**
* A shipment order recording client's requirements on weight, size and destination.
* @int weight - The weight of package
* @double size - The volume of package
* @char dest[] - The destination coordinate string
*/
struct Shipment {
	int weight;
	double size;
	char dest[MAX_DEST_LEN];
};

int getShipmentFromInput(int weight, double size, const char dest[], struct Shipment* shipment);
int dispatchTruck(const struct Truck trucks[], int weight, double size);
struct Point convertStrToPoint(const char* dest);
const char* convertPointToStr(const struct Point* point);
const char* listShortestDiversion(const struct Route* diversion);

#endif