-----------------------------------------------------
Important notes of the program algorithm
-----------------------------------------------------

Input to create order, checking constraint:
1. weight <= MAX_WEIGHT
2. volume <= MAX_VOLUME
3. destination (A <= x <= Y & 1 <= y <= 25)

-----------------------------------------------------

Truck selection criteria:
1. Reachable to destination by calculating min. distance by recusive A* algorithm
2. More available weight / volume

Limiting factor: weight & volume
E.g.
900 kg vs 10 m^3	limiting factor: weight
200 kg vs 30 m^3	limiting factor: volume
Compare by %weight / %volume

-----------------------------------------------------
Functions in mapping module to be used in main logic
-----------------------------------------------------

- struct Map populateMap()
- struct Route getBlueRoute()
- struct Route getGreenRoute()
- struct Route getYellowRoute()
- struct Map addRoute(const struct Map* map, const struct Route* route)
- void printMap(const struct Map* map, const int base1, const int alphaCols)
- int getClosestPoint(const struct Route* route, const struct Point pt)
- struct Route shortestPath(const struct Map* map, const struct Point start, const struct Point dest)

-----------------------------------------------------
Pseudocode
-----------------------------------------------------

Main logic:
-----------

struct Truck[3] containing blue, green, yellow truck, initiating them.

Loop do while (wrong inputs / not quit signal):
	if getShipmentFromInput()
		Calculate min distance for all routes:
			For each Truck,	update minDistance by calculateMinDistance(Truck, convertStrToPoint(Shipment.dest))			
		Check which #truck has more room to be dispatched -> dispatchTruck(Truck[])
		if #truck != -1
			Print "Ship on <Truck color> LINE, "
			Diversion = shortestPath (From mapping module)
			if Diversion contain no Point
				Print "no diversion"
			else
				list shortest diversion -> listShortestDiversion(Diversion)
		else
			Print "Ships tomorrow"
End loop

Print "Thanks for shipping with Seneca!"



Functions in Delivery modules:
------------------------------

1. int getShipmentFromInput()
	isValid = true
	Print "Enter shipment weight, box size and destination (0 0 x to stop): ".
	Get user input in format "<int weight> <double size> <char dest[]>".
	if dest[] out of map (A <= x <= Y & 1 <= y <= 25)
		Print "Invalid destination"
		Mark isValid = false
	if size not in selection (0.25 / 0.5 / 1)
		Print "Invalid size"
		Mark isValid = false
	if weight out of range 1-1000
		Print "Invalid weight (must be 1-1000 Kg.)"
		Mark isValid = false
	if isValid
		Store weight, size and dest[] to struct Shipment: storeShipment(weight, size, dest[])
	return isValid

2. void storeShipment(int weight, double size, const char* dest[])
	Fill the parameters into member data of Shipment object.

3. double calculateMinDistance(const struct Truck* truck, const struct Point* dest)
	Get the route the truck runs on.
	Find nearest point on route -> getClosestPoint(truck route, &dest) (From mapping module)
	Calculate min distance -> shortestPath (From mapping module)
	Total distance = route until nearest point + min distance
	Return total distance.
	
4. int dispatchTruck(const struct Truck[])
	Sort by minDistance, isReady, %weight and %volume.
	if no truck is ready
		Return -1
	else
		Update the weight and volume of the 1st Truck.
		Return index of the 1st Truck

5. struct Point convertStrToPoint(const char* dest)
	Convert string to Point object.

6. const char* convertPointToStr(const struct Point* point)
	Convert Point object to string.

7. void listShortestDiversion(const struct Route* diversion)
	Print all the points in a Route in string format.

-----------------------------------------------------
Shortest Distance Calculation Explained
-----------------------------------------------------

Distance calculation: assigned route + diversion
Diversion: distance travelled from assigned route (White cell)
Min. diversion
Black cell blocks the path

Case 1 - Destination: 7F
Observation:
diversion (B, 7F) = diversion (G, 7F)
diversion (Y, 7F) != diversion (B/G, 7F)
diversion (Y, 7F) => 3
diversion (B/G, 7F) => 2

Min. => B/G

Case 2 - Destination: 8P
Observation:
diversion (B, 8P) ~ diversion (G, 8P)
diversion (B: 11K, 8P) => sqrt(3^2 + 5^2) = 5.83
diversion (G: 6T, 8P) = diversion (G: 10T, 8P) => sqrt(4^2 + 2^2) = 4.47
diversion (G: 8T, 8P) = 4 (blocked)
=> A* algorithm: Calculate the distance between all non-building adjacent cells and destination 

A*(8T, 8P):

  S T U
7|X * *
8|X @ *
9|X * *

@ Current cell (8T) 
* Non-building adjacent cell (7T, 7U, 8U, 9T, 9U)
X Building cell

diversion (G: 7T, 8P) = 4.12
diversion (G: 7U, 8P) = 5.1
diversion (G: 8U, 8P) = 5
diversion (G: 9T, 8P) = 4.12
diversion (G: 9U, 8P) = 5.1
Min. => 7T / 9T
=> 7T (random)

A*(7T, 8P)

  S T U
6|* * *
7|X @ *
8|X * *

...

Repeatedly run A* algorithm until destination is reached
<!> Cannot reverse the path
<!> Unreachable if dead looping

