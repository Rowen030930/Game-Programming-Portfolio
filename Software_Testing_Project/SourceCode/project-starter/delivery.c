#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapping.h"
#include "delivery.h"


int getShipmentFromInput(int weight, double size, const char dest[], struct Shipment* shipment) {
	int isValid = 1;
	struct Point pt = { -1, -1 };

	pt = convertStrToPoint(dest);
	//printf("Input: weight => %d size => %lf Col => %d Row => %d\n", weight, size, pt.col, pt.row);
	if (pt.col < 0 || pt.col > 24 || pt.row < 0 || pt.row > 24) {
		printf("Invalid destination\n");
		isValid = 0;
	}
	if ((size * 1000) != 250 && (size * 1000) != 500 && (size * 1000) != 1000) {
		printf("Invalid size\n");
		isValid = 0;
	}
	if (weight < 1 || weight > 1000) {
		printf("Invalid weight (must be 1-1000 Kg.)\n");
		isValid = 0;
	}
	if (isValid) {
		shipment->weight = weight;
		shipment->size = size;
		strcpy(shipment->dest, convertPointToStr(&pt));
	}
	
	return isValid;
}
int dispatchTruck(const struct Truck trucks[], int weight, double size) {
	int i,
		dispatchIdx = -1;
	double weightPer,
		volumePer,
		minWeightPer = 2,
		minVolumePer = 2,
		minDistance = 9999;	

	for (i = 0; i < NUM_OF_TRUCKS; i++) {
		//printf("i => %d isReady => %d minD => %lf W => %d total W => %d V => %lf total V => %lf\n", i, trucks[i].isReady, trucks[i].minDistance, trucks[i].weight, trucks[i].weight + weight, trucks[i].volume, trucks[i].volume + size);
		if (trucks[i].isReady &&
			trucks[i].weight + weight <= MAX_WEIGHT &&
			trucks[i].volume + size <= MAX_VOLUME
			) {
			//printf("eligible\n");
			weightPer = (double)trucks[i].weight / (double)MAX_WEIGHT;
			volumePer = trucks[i].volume / MAX_VOLUME;
			//printf("<= minDistance? %d\n", trucks[i].minDistance <= minDistance);
			//printf("< minWeightPer? %d\n", weightPer < minWeightPer);
			//printf("< minVolumePer? %d\n", volumePer < minVolumePer);
			if (trucks[i].minDistance < minDistance || (trucks[i].minDistance == minDistance && (weightPer < minWeightPer || volumePer < minVolumePer))) {
				minDistance = trucks[i].minDistance;
				minWeightPer = weightPer;
				minVolumePer = volumePer;
				dispatchIdx = i;
				//printf("dispatchIdx => %d minD => %lf weight%% => %d size%% => %lf\n\n", dispatchIdx, trucks[i].minDistance, trucks[i].weight, trucks[i].volume);
			}
		}
	}
	return dispatchIdx;
}
struct Point convertStrToPoint(const char* dest) {
	char row[3] = { '\0' };
	char col = '\0';
	struct Point res = { -1, -1 };

	if (dest != NULL) {
		if (strlen(dest) == 2) {
			strncpy(row, dest, 1);
			col = dest[1];
		}
		else if (strlen(dest) == 3) {
			strncpy(row, dest, 2);
			col = dest[2];
		}
		res.row = row[0] != '\0' ? atoi(row) - 1 : -1;
		res.col = (int) toupper(col) - 65;
	}
	
	return res;
}
const char* convertPointToStr(const struct Point* point) {
	char dest[5] = { '\0' };
	char col[2] = { '\0' };
	char row[4] = { '\0' };

	if (point != NULL) {
		_itoa(point->row + 1, row, 10);
		col[0] = (char)(point->col + 65);
		strcat(dest, row);
		strcat(dest, col);
	}
	
	return dest;
}
const char* listShortestDiversion(const struct Route* diversion) {
	int i;
	char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };
	if (diversion != NULL) {
		for (i = 0; i < diversion->numPoints && i < MAX_ROUTE; i++) {
			char dest[5] = "";
			strcpy(dest, convertPointToStr(&(diversion->points[i])));
			strcat(res, dest);
			if (i < diversion->numPoints - 1) {
				strcat(res, ", ");
			}
		}
	}
	
	return res;
}