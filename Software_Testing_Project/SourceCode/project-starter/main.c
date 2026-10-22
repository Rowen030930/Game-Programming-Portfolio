#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "mapping.h"
#include "delivery.h"

int main(void)
{
	struct Map baseMap = populateMap();
	struct Map routeMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route* currRoute = NULL;
	struct Route* currDiv = NULL;
	struct Truck trucks[3] = {
		{BLUE, 0, 0.0, 0.0, 1},
		{GREEN, 0, 0.0, 0.0, 1},
		{YELLOW, 0, 0.0, 0.0, 1}
	};
	struct Shipment shipment = { 0, 0, "" };
	struct Route diversionB = { {0,0},0,0 };
	struct Route diversionG = { {0,0},0,0 };
	struct Route diversionY = { {0,0},0,0 };
	struct Route testDiv = { {0,0},0,0 };
	struct Point nearest = { -1, -1 };
	struct Point target = { -1, -1 };
	int isValid = 1,
		isQuit = 0,
		inputRes = 0,
		weight,
		dispatchIdx = -1,
		i, j, k;
	double size,
		testDistance = 0.0,
		minDistance = 999999.0;
	char dest[5] = { '\0' },
		testPoint[5] = { '\0' },
		res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' },
		truckColor[7] = { '\0' };
	

	do {
		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		inputRes = scanf("%d %lf %3s", &weight, &size, dest);

		if (!inputRes) {
			printf("Invalid input\n");
			while ((getchar()) != '\n');
		} else {
			currRoute = NULL;
			currDiv = NULL;
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));

			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {				
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				//printf("Shipment:\nWeight => %d\nSize => %lf\nDestination => %s\n", shipment.weight, shipment.size, shipment.dest);
				target = convertStrToPoint(shipment.dest);
				//printf("Target Point: Col => %d Row => %d\n\n", target.col, target.row);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						//printf("-------------- BLUE --------------\n");
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						//printf("-------------- GREEN --------------\n");
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						//printf("-------------- YELLOW --------------\n");
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (k = 0; k < currDiv->numPoints; k++) {
						currDiv->points[k].col = 0;
						currDiv->points[k].row = 0;
					}
					currDiv->numPoints = 0;
					
					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						if (eqPt(testDiv.points[testDiv.numPoints - 1], target)) {
							for (k = 1; k < testDiv.numPoints; k++) {
								testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
							}
							if (testDistance != 0 && testDistance < minDistance) {
								*currDiv = testDiv;
								trucks[i].minDistance = testDistance;
								minDistance = testDistance;
							}
						}
					}

					//strcpy(res, listShortestDiversion(currDiv));
					//printf("Result | min. Distance: %lf | Shortest divert: %s\n\n", trucks[i].minDistance, res);
				}

				dispatchIdx = !(trucks[0].minDistance == 0.0 && trucks[1].minDistance == 0.0 && trucks[0].minDistance == 0.0) ? dispatchTruck(trucks, shipment.weight, shipment.size) : -1;

				if (dispatchIdx != -1) {
					trucks[dispatchIdx].weight += shipment.weight;
					trucks[dispatchIdx].volume += shipment.size;
					if (trucks[dispatchIdx].weight == MAX_WEIGHT || MAX_VOLUME - trucks[dispatchIdx].volume <= 0.25) {
						trucks[dispatchIdx].isReady = 0;
					}

					switch (trucks[dispatchIdx].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						strcpy(truckColor, "BLUE");
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						strcpy(truckColor, "GREEN");
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						strcpy(truckColor, "YELLOW");
						break;
					}

					printf("Ship on %s LINE, ", truckColor);

					if (currDiv->numPoints > 2) {
						strcpy(res, listShortestDiversion(currDiv));						
						printf("divert: %s\n", res);
						struct Route displayDiv = { {0,0},0,DIVERSION };
						for (int i = 0; i < currDiv->numPoints; i++) {
							if (i != 0 && i != currDiv->numPoints - 1) {
								addPtToRoute(&displayDiv, currDiv->points[i]);
							}
						}
						routeMap = addRoute(&routeMap, &displayDiv);						
					}
					else if (currDiv->numPoints == 2) {
						printf("no diversion\n");
					}
					else {
						printf("Ships tomorrow\n");
					}

					//putchar('\n');
					//printMap(&routeMap, 1, 1);
					//putchar('\n');
				}
				else {
					printf("Ships tomorrow\n");
				}
				
			}
		}
	} while (!isQuit);	

	printf("Thanks for shipping with Seneca!");	

	return 0;
}