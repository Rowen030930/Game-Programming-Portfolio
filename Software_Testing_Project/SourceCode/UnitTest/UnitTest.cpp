#include <cstring>
#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "delivery_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	struct Route testRoute = {
		{
			{0, 0},
			{1, 0},
			{2, 0},
			{3, 0},
			{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8},{4, 9},
			{5, 9},
			{6, 9},
			{7, 9},
			{8, 9},
			{9, 9},
			{10, 9},{10, 10},
			{11, 10},
			{12, 10},
			{13, 10},
			{14, 10},
			{15, 10},
			{16, 10},
			{17, 10},{17, 11},{17, 12},{17, 13},{17, 14},{17, 15},{17, 16},{17, 17},{17, 18},{17, 19},{17, 20},
				{17, 21},{17, 22},{17, 23},{17, 24},
		},
			42, BLUE
	};
	TEST_CLASS(UnitTestMapping)
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup");
		}

		TEST_METHOD(getClosestPointBlackPositive1)
		{
			Logger::WriteMessage("Black-box positive case: Calculate the closest point in Blue route from a valid target Point");
			struct Point target = { 23, 8 };
			int ret = getClosestPoint(&testRoute, target);
			Assert::AreEqual(27, ret);
		}
	};
	TEST_CLASS(UnitTestDelivery)
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup");
		}
		TEST_METHOD(getShipmentFromInputBlackPositive1)
		{
			struct Shipment shipment = { 0, 0, "" };
			Logger::WriteMessage("Black-box positive case: Validate a valid user inputs");
			int isValid = getShipmentFromInput(20, 0.5, "16f", &shipment);
			Assert::AreEqual(1, isValid);
			Assert::AreEqual(20, shipment.weight);
			Assert::AreEqual(0.5, shipment.size);
			Assert::AreEqual("16F", shipment.dest);
		}

		TEST_METHOD(BB_TT_01)
		{
			Logger::WriteMessage("Black-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("3B");
			Assert::AreEqual(2, (int)ret.row);
			Assert::AreEqual(1, (int)ret.col);
		}

		TEST_METHOD(BB_TT_02)
		{
			Logger::WriteMessage("Black-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("1A");
			Assert::AreEqual(0, (int)ret.row);
			Assert::AreEqual(0, (int)ret.col);
		}

		TEST_METHOD(BB_TT_03)
		{
			Logger::WriteMessage("Black-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("26Z");
			Assert::AreEqual(25, (int)ret.row);
			Assert::AreEqual(25, (int)ret.col);
		}

		TEST_METHOD(BB_TT_04)
		{
			Logger::WriteMessage("Black-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("12C");
			Assert::AreEqual(11, (int)ret.row);
			Assert::AreEqual(2, (int)ret.col);
		}

		TEST_METHOD(BB_TT_05)
		{
			Logger::WriteMessage("Black-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("05A");
			Assert::AreEqual(4, (int)ret.row);
			Assert::AreEqual(0, (int)ret.col);
		}

		TEST_METHOD(BB_TT_06)
		{
			Logger::WriteMessage("Black-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("5c");
			Assert::AreEqual(4, (int)ret.row);
			Assert::AreEqual(2, (int)ret.col);
		}

		TEST_METHOD(BB_TT_07)
		{
			Logger::WriteMessage("Black-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("-5G");
			Assert::AreEqual(-6, (int)ret.row);
			Assert::AreEqual(6, (int)ret.col);
		}

		TEST_METHOD(BB_TT_08)
		{
			Logger::WriteMessage("Black-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("A1");
			Assert::AreEqual(-1, (int)ret.row);
			Assert::AreEqual(-16, (int)ret.col);
		}

		TEST_METHOD(BB_TT_09)
		{
			Logger::WriteMessage("Black-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("27A");
			Assert::AreEqual(26, (int)ret.row);
			Assert::AreEqual(0, (int)ret.col);
		}

		TEST_METHOD(WB_TT_01)
		{
			Logger::WriteMessage("White-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("\n");
			Assert::AreEqual(-1, (int)ret.row);
			Assert::AreEqual(-65, (int)ret.col);
		}

		TEST_METHOD(WB_TT_02)
		{
			Logger::WriteMessage("White-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint(" ");
			Assert::AreEqual(-1, (int)ret.row);
			Assert::AreEqual(-65, (int)ret.col);
		}

		TEST_METHOD(WB_TT_03)
		{
			Logger::WriteMessage("White-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("\0");
			Assert::AreEqual(-1, (int)ret.row);
			Assert::AreEqual(-65, (int)ret.col);
		}

		TEST_METHOD(WB_TT_04)
		{
			Logger::WriteMessage("White-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("100A");
			Assert::AreEqual(-1, (int)ret.row);
			Assert::AreEqual(-65, (int)ret.col);
		}

		TEST_METHOD(WB_TT_05)
		{
			Logger::WriteMessage("White-box positive case: Convert valid coordinate label to struct Point");
			struct Point ret = convertStrToPoint("1!");
			Assert::AreEqual(0, (int)ret.row);
			Assert::AreEqual(-32, (int)ret.col);
		}
		TEST_METHOD(BB_DT_001)
		{
			Logger::WriteMessage("Black-box General Case: Convert valid struct Point to coordinate label");
			struct Point pt = { 3, 1 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("4B", ret);
		}

		TEST_METHOD(BB_DT_002)
		{
			Logger::WriteMessage("Black-box Minimum Input Tange case: Convert valid struct Point to coordinate label");
			struct Point pt = { 0, 0 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("1A", ret);
		}

		TEST_METHOD(BB_DT_003)
		{
			Logger::WriteMessage("Black-box Maximum Input Range case: Convert valid struct Point to coordinate label");
			struct Point pt = { 24, 24 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("25Y", ret);
		}

		TEST_METHOD(BB_DT_004)
		{
			Logger::WriteMessage("Black-box NULL Input (Row) case: Convert valid struct Point to coordinate label");
			struct Point pt = { 5, NULL };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("6A", ret);
		}

		TEST_METHOD(BB_DT_005)
		{
			Logger::WriteMessage("Black-box NULL Input (Col) case: Convert valid struct Point to coordinate label");
			struct Point pt = { NULL, 5 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("1F", ret);
		}

		TEST_METHOD(BB_DT_006)
		{
			Logger::WriteMessage("Black-box NULL Input (Row and Col) case: Convert valid struct Point to coordinate label");
			struct Point pt = { NULL, NULL };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("1A", ret);
		}

		TEST_METHOD(BB_DT_007)
		{
			Logger::WriteMessage("Black-box Row Edge Case case: Convert valid struct Point to coordinate label");
			struct Point pt = { 5, 24 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("6Y", ret);
		}

		TEST_METHOD(BB_DT_008)
		{
			Logger::WriteMessage("Black-box Col Edge Case case: Convert valid struct Point to coordinate label");
			struct Point pt = { 24, 5 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("25F", ret);
		}

		TEST_METHOD(WB_DT_001)
		{
			Logger::WriteMessage("White-box Negative case (Row) case: Convert valid struct Point to coordinate label");
			struct Point pt = { 15, -10 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("167", ret);
		}

		TEST_METHOD(WB_DT_002)
		{
			Logger::WriteMessage("White-box Negative case (Col) case: Convert valid struct Point to coordinate label");
			struct Point pt = { -10, 5 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("-9F", ret);
		}

		TEST_METHOD(WB_DT_003)
		{
			Logger::WriteMessage("White-box Large Row Value Case case: Convert valid struct Point to coordinate label");
			struct Point pt = { 1, 50 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("2s", ret);
		}

		TEST_METHOD(WB_DT_004)
		{
			Logger::WriteMessage("White-box Large Col Value Case case: Convert valid struct Point to coordinate label");
			struct Point pt = { 50, 1 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("51B", ret);
		}

		TEST_METHOD(WB_DT_005)
		{
			Logger::WriteMessage("White-box arge Row and Column Value Calculation case: Convert valid struct Point to coordinate label");
			struct Point pt = { 50, 50 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("51s", ret);
		}

		TEST_METHOD(WB_DT_006)
		{
			Logger::WriteMessage("White-box Zero Value Calculation (Row) case: Convert valid struct Point to coordinate label");
			struct Point pt = { 15, 0 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("16A", ret);
		}

		TEST_METHOD(WB_DT_007)
		{
			Logger::WriteMessage("White-box Zero Value Calculation (Col) case: Convert valid struct Point to coordinate label");
			struct Point pt = { 0, 15 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("1P", ret);
		}

		TEST_METHOD(WB_DT_008)
		{
			Logger::WriteMessage("White-box Special symbol Input (Row) case: Convert valid struct Point to coordinate label");
			struct Point pt = { 15, '#' };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("16d", ret);
		}

		TEST_METHOD(WB_DT_009)
		{
			Logger::WriteMessage("White-box Special symbol Input (Col) case: Convert valid struct Point to coordinate label");
			struct Point pt = { '#', 5 };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("36F", ret);
		}

		TEST_METHOD(WB_DT_010)
		{
			Logger::WriteMessage("White-box Special symbol Input (Row + Col) case: Convert valid struct Point to coordinate label");
			struct Point pt = { '#', '#' };
			char ret[4] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("36d", ret);
		}

		/*TEST_METHOD(WB_DT_013)
		{
			Logger::WriteMessage("White-box Special Col over 2-digit case: Convert valid struct Point to coordinate label");
			struct Point pt = { 99, 1 };
			char ret[5] = { '\0' };
			strcpy_s(ret, convertPointToStr(&pt));
			Assert::AreEqual("100B", ret);
		}*/

		TEST_METHOD(UT_DT_B01)
		{
			Logger::WriteMessage("Black-box positive case: refer to UT_DT_B01 in test-description (dispatchTruck)");
			const struct Truck trucks[] = { { 2, 0, 0.0, 4.5, 1 }, { 4, 0, 0.0, 4.6, 1 }, { 8, 0, 0.0, 4.7, 1 } };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B02)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: No trucks are loaded, 1 shortest distance, all enough capacities");
			const struct Truck trucks[] = { {2, 1, 1.1, 4.5, 1}, {4, 2, 2.2, 4.6, 1}, {8, 2, 3.3, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B03)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded and same diversion distance, just 1 truck has enough capacity (in terms of weight)");
			const struct Truck trucks[] = { {2, 4, 2.2, 3.3, 1}, {4, 5, 2.2, 3.3, 1}, {8, 2, 2.2, 3.3, 1} };
			int weight = 998;
			double size = 1.1;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(2, result);
		}
		TEST_METHOD(UT_DT_B04)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded and same diversion distance, just 1 truck has enough capacity (in terms of volume)");
			const struct Truck trucks[] = { {2, 4, 1.4, 3.3, 1}, {4, 5, 0.3, 3.3, 1}, {8, 2, 1.5, 3.3, 1} };
			int weight = 1;
			double size = 35.7;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(UT_DT_B05)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, same diversion distance, same capacity, just 1 truck isReady");
			const struct Truck trucks[] = { {2, 5, 0.3, 3.3, 1}, {4, 5, 0.3, 3.3, 1}, {8, 5, 0.3, 3.3, 1} };
			int weight = 1;
			double size = 35.7;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B06)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, 1 truck with shortest diversion distance but not enough capacity (in terms of weight), other trucks have enough capacity and different diversion distance, all trucks isReady");
			const struct Truck trucks[] = { {2, 4, 0.1, 1.2, 1}, {4, 3, 0.1, 1.3, 1}, {8, 3, 0.1, 1.4, 1} };
			int weight = 997;
			double size = 3.4;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(UT_DT_B07)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, 1 truck with shortest diversion distance but not enough capacity (in terms of volume), other trucks have enough capacity and different diversion distance, all trucks isReady");
			const struct Truck trucks[] = { {2, 4, 0.1, 10.1, 1}, {4, 4, 0.4, 2.8, 1}, {8, 4, 0.1, 0.3, 1} };
			int weight = 1;
			double size = 35.1;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(2, result);
		}
		TEST_METHOD(UT_DT_B08)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, 1 truck with shortest diversion distance but notReady, other trucks have enough capacity with different diversion distance and isReady");
			const struct Truck trucks[] = { {2, 4, 0.3, 1.3, 0}, {4, 4, 0.3, 1.4, 1}, {8, 4, 0.3, 1.5, 1} };
			int weight = 456;
			double size = 9;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(UT_DT_B09)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, 1 truck with shortest diversion distance but notReady, other trucks have enough capacity with different diversion distance and isReady");
			const struct Truck trucks[] = { {2, 4, 0.3, 1.3, 0}, {4, 999, 0.3, 1.4, 1}, {8, 998, 0.3, 1.4, 1} };
			int weight = 1;
			double size = 10;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(2, result);
		}
		TEST_METHOD(UT_DT_B10)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, 1 truck with shortest diversion distance but notReady, other trucks have same diversion distance and isReady, both can hold the package but different capacity (in terms of volume)");
			const struct Truck trucks[] = { {2, 4, 0.3, 1.3, 0}, {4, 1, 10.1, 3.5, 1}, {8, 1, 10.2, 3.5, 1} };
			int weight = 50;
			double size = 1.2;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(UT_DT_B11)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, 2 trucks with shortest diversion distance but notReady, remaining truck have enough capacity with higher diversion distance and isReady");
			const struct Truck trucks[] = { {2, 4, 0.3, 7.8, 1}, {4, 1, 10.1, 3.5, 0}, {8, 1, 10.1, 3.5, 0} };
			int weight = 1;
			double size = 1.1;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B12)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: 1 truck notReady. Other trucks loaded, same shortest diversion distance and isReady, 1 truck with very low weight but very high volume. Volume should be limiting factor.");
			const struct Truck trucks[] = { {2, 10, 3.2, 3.5, 1}, {4, 0.1, 35.5, 3.5, 1}, {8, 10, 7.2, 3.5, 0} };
			int weight = 1;
			double size = 1.1;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B13)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, same shortest diversion distance, have enough capacities, but notReady");
			const struct Truck trucks[] = { {2, 995, 0.1, 3.5, 0}, {4, 100, 1.1, 3.5, 0}, {8, 10, 7.2, 3.5, 0} };
			int weight = 1;
			double size = 1.1;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(UT_DT_B14)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, same shortest diversion distance, have enough capacities, but notReady");
			const struct Truck trucks[] = { {2, 995, 0.1, 3.5, 0}, {4, 100, 1.1, 3.5, 0}, {8, 10, 7.2, 3.5, 0} };
			int weight = 1;
			double size = 1.1;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(UT_DT_B15)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, same shortest diversion distance, isReady, but not enough capacities (in terms of weight)");
			const struct Truck trucks[] = { {2, 995, 0.1, 3.5, 1}, {4, 100, 1.1, 3.5, 1}, {8, 10, 7.2, 3.5, 1} };
			int weight = 999;
			double size = 1.1;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(UT_DT_B16)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, same shortest diversion distance, isReady, but not enough capacities (in terms of volume)");
			const struct Truck trucks[] = { {2, 995, 0.5, 3.5, 1}, {4, 100, 1.1, 3.5, 1}, {8, 10, 7.2, 3.5, 1} };
			int weight = 1;
			double size = 35.9;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(UT_DT_B17)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: All trucks loaded, same shortest diversion distance, 1 notReady, others not enough capacities (in terms of weight or volume)");
			const struct Truck trucks[] = { {2, 10, 1.1, 3.5, 0}, {4, 900, 1.1, 3.5, 1}, {8, 10, 35, 3.5, 1} };
			int weight = 500;
			double size = 15;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(UT_DT_B18)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: Input characters for routeSymbol");
			const struct Truck trucks[] = { {'a', 0, 0.0, 4.5, 1}, {'b', 0, 0.0, 4.6, 1}, {'c', 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B19)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: Input special characters for routeSymbol");
			const struct Truck trucks[] = { {'?', 0, 0.0, 4.5, 1}, {'+', 0, 0.0, 4.6, 1}, {'=', 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B20)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: Input ' ' for routeSymbol");
			const struct Truck trucks[] = { {' ', 0, 0.0, 4.5, 1}, {' ', 0, 0.0, 4.6, 1}, {' ', 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B21)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: Input '\t' for routeSymbol");
			const struct Truck trucks[] = { {'\t', 0, 0.0, 4.5, 1}, {'\t', 0, 0.0, 4.6, 1}, {'\t', 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B22)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: Input '\n' for routeSymbol");
			const struct Truck trucks[] = { {'\n', 0, 0.0, 4.5, 1}, {'\n', 0, 0.0, 4.6, 1}, {'\n', 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B23)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: Input '\0' for routeSymbol");
			const struct Truck trucks[] = { {'\0', 0, 0.0, 4.5, 1}, {'\0', 0, 0.0, 4.6, 1}, {'\0', 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B24)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: Input double for truck's weight");
			const struct Truck trucks[] = { {2, 0.1, 0.0, 4.5, 1}, {4, 0.1, 0.0, 4.6, 1}, {8, 0.1, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_B25)
		{
			Logger::WriteMessage("Black-box test for dispatchTruck: Input double for truck's weight");
			const struct Truck trucks[] = { {2, 0, 0.0, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1} };
			int weight = 10.1;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		//TEST_METHOD(UT_DT_W01)
		//{
		//	Logger::WriteMessage("White-box test for dispatchTruck: Input more than 3 trucks");
		//	const struct Truck trucks[] = { {2, 0, 0.0, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1}, {10, 0, 0.0, 4.4, 1} };
		//	int weight = 10;
		//	double size = 2.5;
		//	int result = dispatchTruck(trucks, weight, size);
		//	Assert::AreEqual(3, result);
		//}
		TEST_METHOD(UT_DT_W02)
		{
			Logger::WriteMessage("White-box test for dispatchTruck: Input negative truck's weight");
			const struct Truck trucks[] = { {2, -10, 0.0, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_W03)
		{
			Logger::WriteMessage("White-box test for dispatchTruck: Input negative truck's volume");
			const struct Truck trucks[] = { {2, 0, -9.9, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_W04)
		{
			Logger::WriteMessage("White-box test for dispatchTruck: Input negative int weight");
			const struct Truck trucks[] = { {2, 0, 0.0, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1} };
			int weight = -10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_W05)
		{
			Logger::WriteMessage("White-box test for dispatchTruck: Input negative double volume");
			const struct Truck trucks[] = { {2, 0, 0.0, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = -2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(UT_DT_W06)
		{
			Logger::WriteMessage("White-box test for dispatchTruck: Input more than max weight for truck");
			const struct Truck trucks[] = { {2, 99999, 0.0, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(UT_DT_W07)
		{
			Logger::WriteMessage("White-box test for dispatchTruck: Input more than max volume for truck");
			const struct Truck trucks[] = { {2, 0, 99.9, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(UT_DT_W08)
		{
			Logger::WriteMessage("White-box test for dispatchTruck: Input more than max weight for int weight");
			const struct Truck trucks[] = { {2, 0, 0.0, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1} };
			int weight = 99999;
			double size = 2.5;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(UT_DT_W0)
		{
			Logger::WriteMessage("White-box test for dispatchTruck: Input more than max volume for double volume");
			const struct Truck trucks[] = { {2, 0, 0.0, 4.5, 1}, {4, 0, 0.0, 4.6, 1}, {8, 0, 0.0, 4.7, 1} };
			int weight = 10;
			double size = 99.9;
			int result = dispatchTruck(trucks, weight, size);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(UT_LSD_B01)
		{
			Logger::WriteMessage("Black-box positive case: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[3] = { {1, 2}, {2, 2}, {2, 3} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "2C, 3C, 3D"));

		}
		TEST_METHOD(UT_LSD_B02)
		{
			Logger::WriteMessage("Black-box empty diversion path case: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 0;
			mockRoute.routeSymbol = '\0';
			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, ""));
		}
		TEST_METHOD(UT_LSD_B03)
		{
			Logger::WriteMessage("Black-box diversion path containing one point: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 1;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[1] = { {5, 5} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "6F"));
		}
		TEST_METHOD(UT_LSD_B04)
		{
			Logger::WriteMessage("Black-box route symbol is a number: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = '1';
			struct Point mockPoints[3] = { {1, 2}, {2, 2}, {2, 3} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "2C, 3C, 3D"));
		}
		TEST_METHOD(UT_LSD_B05)
		{
			Logger::WriteMessage("Black-box route symbol is an empty character: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = ' ';
			struct Point mockPoints[3] = { {1, 2}, {2, 2}, {2, 3} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "2C, 3C, 3D"));
		}
		TEST_METHOD(UT_LSD_B06)
		{
			Logger::WriteMessage("Black-box route symbol is a special character: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = '@';
			struct Point mockPoints[3] = { {1, 2}, {2, 2}, {2, 3} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "2C, 3C, 3D"));
		}
		//TEST_METHOD(UT_LSD_B07)
		//{
		//	Logger::WriteMessage("Black-box route symbol is '\\0': Test listShortestDiversion function");
		//	struct Route mockRoute;
		//	mockRoute.numPoints = 3;
		//	mockRoute.routeSymbol = '\0';
		//	struct Point mockPoints[3] = { {1, 2}, {2, 2}, {2, 3} };
		//	for (int i = 0; i < mockRoute.numPoints; i++)
		//		mockRoute.points[i] = mockPoints[i];
		//	Assert::IsNull(listShortestDiversion(&mockRoute)); 
		//}
		//TEST_METHOD(UT_LSD_B08)
		//{
		//	Logger::WriteMessage("Black-box route symbol is '\\n': Test listShortestDiversion function");
		//	struct Route mockRoute;
		//	mockRoute.numPoints = 3;
		//	mockRoute.routeSymbol = '\n';
		//	struct Point mockPoints[3] = { {1, 2}, {2, 2}, {2, 3} };
		//	for (int i = 0; i < mockRoute.numPoints; i++)
		//		mockRoute.points[i] = mockPoints[i];
		//	Assert::IsNull(listShortestDiversion(&mockRoute));
		//}
		//TEST_METHOD(UT_LSD_B09)
		//{
		//	Logger::WriteMessage("Black-box route symbol is '\t': Test listShortestDiversion function");
		//	struct Route mockRoute;
		//	mockRoute.numPoints = 3;
		//	mockRoute.routeSymbol = '\t';
		//	struct Point mockPoints[3] = { {1, 2}, {2, 2}, {2, 3} };
		//	for (int i = 0; i < mockRoute.numPoints; i++)
		//		mockRoute.points[i] = mockPoints[i];
		//	Assert::IsNull(listShortestDiversion(&mockRoute));
		//}
		TEST_METHOD(UT_LSD_B10)
		{
			Logger::WriteMessage("Black-box diversion path containing duplicate points: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[3] = { {1, 2}, {1, 2}, {2, 2} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "2C, 2C, 3C"));
			//Assert::IsNull(result); 
		}
		TEST_METHOD(UT_LSD_B11)
		{
			Logger::WriteMessage("Black-box diversion path where the points are randomly scattered: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[3] = { {1, 2}, {12, 12}, {22, 23} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "2C, 13M, 23X"));
			//Assert::IsNull(result); 
		}
		TEST_METHOD(UT_LSD_B12)
		{
			Logger::WriteMessage("Black-box diversion path where all points are on a straight line (hor): Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[3] = { {1, 1}, {1, 2}, {1, 3} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "2B, 2C, 2D"));
		}
		TEST_METHOD(UT_LSD_B13)
		{
			Logger::WriteMessage("Black-box diversion path where all points are on a straight line (ver): Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[3] = { {1, 1}, {2, 1}, {3, 1} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "2B, 3B, 4B"));
		}
		TEST_METHOD(UT_LSD_B14)
		{
			Logger::WriteMessage("Black-box diversion path where all points are on a curved line: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[3] = { {1, 1}, {2, 2}, {3, 1} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "2B, 3C, 4B"));
		}
		TEST_METHOD(UT_LSD_B15)
		{
			Logger::WriteMessage("Black-box diversion path where some points are on the truck route: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[3] = { {2, 0}, {2, 1}, {2, 2} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "3A, 3B, 3C"));
		}
		//TEST_METHOD(UT_LSD_W01)
		//{
		//	const struct Route* diversion = nullptr;
		//	const char* result = listShortestDiversion(diversion);
		//	Assert::AreEqual(nullptr, result);
		//	//Assert::IsNull(result);
		//}
		//TEST_METHOD(UT_LSD_W02)
		//{
		//	Logger::WriteMessage("White-box diversion path containing points outside the map boundaries: Test listShortestDiversion function");
		//	struct Route mockRoute;
		//	mockRoute.numPoints = 4;
		//	mockRoute.routeSymbol = 'A';
		//	struct Point mockPoints[4] = { {-1, 1}, {0, 1}, {1, 1}, {2, 2} };
		//	for (int i = 0; i < mockRoute.numPoints; i++)
		//		mockRoute.points[i] = mockPoints[i];
		//	Assert::IsNull(listShortestDiversion(&mockRoute));
		//}
		TEST_METHOD(UT_LSD_W03)
		{
			Logger::WriteMessage("White-box diversion path containing points on the map boundaries: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 3;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[3] = { {0, 1}, {0, 2}, {2, 2} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "1B, 1C, 3C"));
		}

		TEST_METHOD(UT_LSD_W04)
		{
			Logger::WriteMessage("White-box diversion path containing points on the map boundaries corner(TL): Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 1;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[1] = { {0, 0} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "1A"));
		}

		TEST_METHOD(UT_LSD_W05)
		{
			Logger::WriteMessage("White-box diversion path containing points on the map boundaries corner(TR): Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 1;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[1] = { {0, 25} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "1Z"));
		}

		TEST_METHOD(UT_LSD_W06)
		{
			Logger::WriteMessage("White-box diversion path containing points on the map boundaries corner(BL): Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 1;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[1] = { {25, 0} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "26A"));
		}

		TEST_METHOD(UT_LSD_W07)
		{
			Logger::WriteMessage("White-box diversion path containing points on the map boundaries corner(BR): Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 1;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[1] = { {25, 25} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "26Z"));
		}

		//TEST_METHOD(UT_LSD_W08)
		//{
		//	Logger::WriteMessage("White-box numPoints greater than the array of Point size: Test listShortestDiversion function");
		//	struct Route mockRoute;
		//	mockRoute.numPoints = 4;
		//	mockRoute.routeSymbol = 'A';
		//	struct Point mockPoints[3] = { {2, 0}, {2, 1}, {2, 2} };
		//	for (int i = 0; i < 3; i++)
		//		mockRoute.points[i] = mockPoints[i];
		//	const char* result = listShortestDiversion(&mockRoute);
		//	Assert::IsNull(result);
		//}
		TEST_METHOD(UT_LSD_W09)
		{
			Logger::WriteMessage("White-box numPoints smaller than the array of Point size: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = 2;
			mockRoute.routeSymbol = 'A';
			struct Point mockPoints[3] = { {2, 0}, {2, 1}, {2, 2} };
			for (int i = 0; i < mockRoute.numPoints; i++)
				mockRoute.points[i] = mockPoints[i];

			const char* resultttt = convertPointToStr(&mockPoints[0]);
			Assert::AreEqual(0, strcmp(resultttt, "3A"));

			const char* result = listShortestDiversion(&mockRoute);
			Assert::AreEqual(0, strcmp(result, "3A, 3B"));
			//Assert::IsNull(result);
		}

		TEST_METHOD(UT_LSD_W10)
		{
			Logger::WriteMessage("White-box diversion path with [MAX_ROUTE-1] number of points: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = MAX_ROUTE - 1;
			mockRoute.routeSymbol = 'A';
			for (int i = 0; i < MAX_ROUTE - 1; i++)
			{
				mockRoute.points[i].row = 1;
				mockRoute.points[i].col = 1;
			}

			char result[500] = { '\0' };
			strcpy_s(result, 500, listShortestDiversion(&mockRoute));
			char expectedResult[500] = { '\0' };
			for (int i = 0; i < MAX_ROUTE - 1; i++)
			{
				if (i != 0) strcat_s(expectedResult, 500, ", ");
				strcat_s(expectedResult, 500, "2B");
			}

			Assert::AreEqual(0, strcmp(result, expectedResult));
		}

		TEST_METHOD(UT_LSD_W11)
		{
			Logger::WriteMessage("White-box diversion path with [MAX_ROUTE] number of points: Test listShortestDiversion function");
			struct Route mockRoute;
			mockRoute.numPoints = MAX_ROUTE;
			mockRoute.routeSymbol = 'A';
			for (int i = 0; i < MAX_ROUTE; i++)
			{
				mockRoute.points[i].row = 1;
				mockRoute.points[i].col = 1;
			}

			char result[500] = { '\0' };
			strcpy_s(result, 500, listShortestDiversion(&mockRoute));
			char expectedResult[500] = { '\0' };
			for (int i = 0; i < MAX_ROUTE; i++)
			{
				if (i != 0) strcat_s(expectedResult, 500, ", ");
				strcat_s(expectedResult, 500, "2B");
			}

			Assert::AreEqual(0, strcmp(result, expectedResult));
		}
		//TEST_METHOD(UT_LSD_W12)
		//{
		//	Logger::WriteMessage("White-box diversion path with [MAX_ROUTE+1] number of points: Test listShortestDiversion function");
		//	struct Route mockRoute;
		//	mockRoute.numPoints = MAX_ROUTE + 1;
		//	mockRoute.routeSymbol = 'A';
		//	for (int i = 0; i < mockRoute.numPoints; i++)
		//	{
		//		mockRoute.points[i].row = 1;
		//		mockRoute.points[i].col = 2;
		//	}
		//	const char* result = listShortestDiversion(&mockRoute);
		//	Assert::IsNull(result); 
		//}

		TEST_METHOD(vaildShipmentInput_UT_GI_B01)
		{
			Logger::WriteMessage("Blackbox - Positive test - minmum weight in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 1;
			double size = 0.25;
			char dest[4] = "16F";

			int result = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result == 1);
		}
		TEST_METHOD(vaildShipmentInput_UT_GI_B02)
		{
			Logger::WriteMessage("Blackbox - Positive test - maximum weight in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 1000;
			double size = 0.25;
			char dest[4] = "16F";

			int result1 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result1 == 1);
		}
		TEST_METHOD(vaildShipmentInput_UT_GI_B06)
		{
			Logger::WriteMessage("Blackbox - Positive test - minmum box size in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = 0.25;
			char dest[4] = "16F";

			int result2 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result2 == 1);
		}
		TEST_METHOD(vaildShipmentInput_UT_GI_B07)
		{
			Logger::WriteMessage("Blackbox - Positive test - maximum box size in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = 1;
			char dest[4] = "16F";

			int result3 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result3 == 1);
		}
		TEST_METHOD(vaildShipmentInput_UT_GI_B12)
		{
			Logger::WriteMessage("Blackbox - Positive test - destination within grid in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = 0.25;
			char dest[4] = "16F";

			int result4 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result4 == 1);
		}

		TEST_METHOD(vaildShipmentInput_UT_GI_B19)
		{
			Logger::WriteMessage("Whitebox - test if shipment in different array size ");
			struct Shipment shipment2[2] = { {0, 0, ""} ,{ 0, 0, "" } };
			int weight = 5;
			double size = 0.25;
			char dest[4] = "16F";

			int result5 = getShipmentFromInput(weight, size, dest, shipment2);
			Assert::IsTrue(result5 == 1);
		}
		TEST_METHOD(InvaildShipmentInput_UT_GI_B03)
		{
			Logger::WriteMessage("Blackbox - Negative test - negetive  weight in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = -1;
			double size = 0.25;
			char dest[4] = "16F";

			int result6 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result6 == 0);
		}
		TEST_METHOD(InvaildShipmentInput_UT_GI_B04)
		{
			Logger::WriteMessage("Blackbox - Negative test - over weight in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 2000;
			double size = 0.25;
			char dest[4] = "16F";

			int result6 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result6 == 0);
		}
		/*TEST_METHOD(InvaildShipmentInput_UT_GI_B05)
		{
			Logger::WriteMessage("Blackbox - Negative test - input type error in weight");
			struct Shipment shipment = { 0, 0, "" };
			int weight = '?';
			double size = 0.25;
			char dest[4] = "16F";

			int result7 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result7 == 0);
		}*/
		TEST_METHOD(InvaildShipmentInput_UT_GI_B08)
		{
			Logger::WriteMessage("Blackbox - Positive test -  box size out of requirement in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = 0.75;
			char dest[4] = "16F";

			int result8 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result8 == 0);
		}
		TEST_METHOD(InvaildShipmentInput_UT_GI_B09)
		{
			Logger::WriteMessage("Blackbox - Positive test -  box size with extra decimal");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = 0.255555;
			char dest[4] = "16F";

			int result9 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result9 == 0);//Bug fixed
		}
		TEST_METHOD(InvaildShipmentInput_UT_GI_B10)
		{
			Logger::WriteMessage("Blackbox - Negative test - negetive box size in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = -1.0;
			char dest[4] = "16F";

			int result10 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result10 == 0);
		}
		/*TEST_METHOD(InvaildShipmentInput_UT_GI_B11)
		{
			Logger::WriteMessage("Blackbox - Negative test - input type error in box size");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = '#';
			char dest[4] = "16F";

			int result11 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result11 == 0);
		}*/
		TEST_METHOD(InvaildShipmentInput_UT_GI_B13)
		{
			Logger::WriteMessage("Blackbox - Negative test - destination row outside grid in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = 0.25;
			char dest[4] = "30L";

			int result12 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result12 == 0);
		}
		TEST_METHOD(InvaildShipmentInput_UT_GI_B14)
		{
			Logger::WriteMessage("Blackbox - Negative test - destination column outside grid in use");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = 0.25;
			char dest[4] = "8Z";

			int result13 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result13 == 0);
		}
		TEST_METHOD(InvaildShipmentInput_UT_GI_B15)
		{
			Logger::WriteMessage("Blackbox - Negative test - incorrect input type in destination");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = 0.25;
			char dest[4] = "#";

			int result14 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result14 == 0);
		}
		TEST_METHOD(InvaildShipmentInput_UT_GI_B16)
		{
			Logger::WriteMessage("Whitebox - To test if function can handle NULL destination");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = 0.25;
			char dest[4] = { NULL };

			int result15 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result15 == 0);
		}
		TEST_METHOD(InvaildShipmentInput_UT_GI_B17)
		{
			Logger::WriteMessage("Whitebox - To test if function can handle NULL weight");
			struct Shipment shipment = { 0, 0, "" };
			int weight = NULL;
			double size = 0.25;
			char dest[4] = "16F";

			int result16 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result16 == 0);
		}
		TEST_METHOD(InvaildShipmentInput_UT_GI_B18)
		{
			Logger::WriteMessage("Whitebox - To test if function can handle NULL size");
			struct Shipment shipment = { 0, 0, "" };
			int weight = 5;
			double size = NULL;
			char dest[4] = "16F";

			int result17 = getShipmentFromInput(weight, size, dest, &shipment);
			Assert::IsTrue(result17 == 0);
		}
	};
	TEST_CLASS(IntegrationTest)
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup");
		}

		TEST_METHOD(UT_G1_B01)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 1;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10M");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B02)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 1000;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10M");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B03)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10M");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B04)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10M");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B05)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 1;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10M");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B06)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "1A");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B07)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "1Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B08)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "25A");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(2, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B09)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "25Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(2, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B10)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "11K");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B11)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "11L");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B12)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "18Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B13)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "5T");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B14)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "5U");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B15)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B16)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0, dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10D");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(2, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B17)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0, dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10E");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(2, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B18)
		{
			Logger::WriteMessage("Blackbox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0, dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "20Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(2, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B19)
		{
			Logger::WriteMessage("Blackbox - To test if the truck with shortest diversion distance can be picked with invalid shipment");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0, 
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 2.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "8Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(-1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B20)
		{
			Logger::WriteMessage("Blackbox - To test if the truck with shortest diversion distance can be picked with invalid shipment (extr decimal)");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.2555556;
			char dest[5] = { '\0' };
			strcpy_s(dest, "8Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(-1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B21)
		{
			Logger::WriteMessage("BBlackbox - To test if the truck with shortest diversion distance can be picked with invalid shipment (negative box size)");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = -0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "8Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(-1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B22)
		{
			Logger::WriteMessage("Blackbox - To test if the truck with shortest diversion distance can be picked with invalid shipment (Invaild box size)");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.75;
			char dest[5] = { '\0' };
			strcpy_s(dest, "8Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(-1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B23)
		{
			Logger::WriteMessage("Blackbox - To test if the truck with shortest diversion distance can be picked with invalid shipment (invaild destination)");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "26P");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(-1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_B24)
		{
			Logger::WriteMessage("Blackbox - To test if the next available truck with shortest diversion distance can be picked with valid shipment");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 500;
			double size = 1;
			char dest[5] = { '\0' };
			strcpy_s(dest, "8Y");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 700, 1.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W01)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 500;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "11K");
			struct Truck trucks[3] = { {2, 500, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W02)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 600;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "11K");
			struct Truck trucks[3] = { {2, 500, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W03)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 500;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "5T");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 500, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W04)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 600;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "5T");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 500, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W05)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 500;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10D");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 500, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(2, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W06)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 600;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10D");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 500, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W07)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 600;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10D");
			struct Truck trucks[3] = { {2, 500, 0.0, 0.0, 1}, {4, 500, 0.0, 0.0, 1}, {8, 500, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(-1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W08)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "11K");
			struct Truck trucks[3] = { {2, 0, 35.5, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W09)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "11K");
			struct Truck trucks[3] = { {2, 0, 35.6, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W10)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "5T");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 35.5, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W11)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 1;
			char dest[5] = { '\0' };
			strcpy_s(dest, "5T");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 35.5, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W12)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.5;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10D");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 35.5, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(2, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W13)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 1;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10D");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 35.5, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(0, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W14)
		{
			Logger::WriteMessage("Whitebox - Please refer to test document for test purpose");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 1;
			char dest[5] = { '\0' };
			strcpy_s(dest, "10D");
			struct Truck trucks[3] = { {2, 0, 35.5, 0.0, 1}, {4, 0, 35.5, 0.0, 1}, {8, 0, 35.5, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(-1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W15)
		{
			Logger::WriteMessage("Whitebox - To test if the truck with shortest diversion distance can be picked with valid shipment (NULL destination)");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = 10;
			double size = 0.25;
			char dest[5] = { '\0' };
			*dest = NULL;
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(-1, dispatchIdx);
		};

		TEST_METHOD(UT_G1_W16)
		{
			Logger::WriteMessage("Whitebox - To test if the truck with shortest diversion distance can be picked with valid shipment (NULL destination)");

			// *** Parameters to be initialized for the testing to work ***
			struct Map baseMap = populateMap();
			struct Map routeMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Route* currRoute = NULL;
			struct Route* currDiv = NULL;
			struct Shipment shipment = { 0, 0, "" };
			struct Route diversionB = { {0,0},0,0 };
			struct Route diversionG = { {0,0},0,0 };
			struct Route diversionY = { {0,0},0,0 };
			struct Route testDiv = { {0,0},0,0 };
			struct Point target = { -1, -1 };
			int isQuit = 0,
				dispatchIdx = -1,
				i, j, k;
			double testDistance = 0.0,
				minDistance = 999999.0;
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			int weight = NULL;
			double size = 0.25;
			char dest[5] = { '\0' };
			strcpy_s(dest, "12L");
			struct Truck trucks[3] = { {2, 0, 0.0, 0.0, 1}, {4, 0, 0.0, 0.0, 1}, {8, 0, 0.0, 0.0, 1} };

			// *** Integration test logic ***
			isQuit = ((weight == 0) && (size == 0) && (strcmp(dest, "x") == 0));
			if (!isQuit && getShipmentFromInput(weight, size, dest, &shipment)) {
				routeMap = addRoute(&baseMap, &blueRoute);
				routeMap = addRoute(&routeMap, &greenRoute);
				routeMap = addRoute(&routeMap, &yellowRoute);
				target = convertStrToPoint(shipment.dest);
				for (i = 0; i < 3; i++) {
					minDistance = 999999.0;
					trucks[i].minDistance = 0;

					switch (trucks[i].routeSymbol) {
					case BLUE:
						currRoute = &blueRoute;
						currDiv = &diversionB;
						break;
					case GREEN:
						currRoute = &greenRoute;
						currDiv = &diversionG;
						break;
					case YELLOW:
						currRoute = &yellowRoute;
						currDiv = &diversionY;
						break;
					}

					for (j = 0; j < currRoute->numPoints; j++) {
						testDistance = 0.0;
						testDiv = shortestPath(&routeMap, currRoute->points[j], target);
						for (k = 1; k < testDiv.numPoints; k++) {
							testDistance += distance(&(testDiv.points[k - 1]), &(testDiv.points[k]));
						}
						if (testDistance < minDistance) {
							*currDiv = testDiv;
							trucks[i].minDistance = testDistance;
							minDistance = testDistance;
						}
					}
					strcpy_s(res, listShortestDiversion(currDiv));
				}

				dispatchIdx = dispatchTruck(trucks, shipment.weight, shipment.size);
			}

			// *** Test results ***
			Assert::AreEqual(-1, dispatchIdx);
		};

		TEST_METHOD(UT_G2_B01)
		{
			Logger::WriteMessage("Blackbox -  general case");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "12L" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("12L", result);
		};

		TEST_METHOD(UT_G2_B02)
		{
			Logger::WriteMessage("Blackbox - Minimum Input Range");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "1A" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("1A", result);
		};

		TEST_METHOD(UT_G2_B03)
		{
			Logger::WriteMessage("Blackbox - Maximum Input Range");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "25Z" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("25Z", result);
		};

		TEST_METHOD(UT_G2_B04)
		{
			Logger::WriteMessage("Blackbox - Missing the character value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "1" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("0", result);
		};

		TEST_METHOD(UT_G2_B05)
		{
			Logger::WriteMessage("Blackbox - Missing the number value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "A" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("0", result);
		};

		TEST_METHOD(UT_G2_B06)
		{
			Logger::WriteMessage("Blackbox - empty value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("0", result);
		};

		TEST_METHOD(UT_G2_B07)
		{
			Logger::WriteMessage("Blackbox - negative number value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "-10C" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("0", result);
		};

		TEST_METHOD(UT_G2_B08)
		{
			Logger::WriteMessage("Blackbox - larger than the original range value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "26Z" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("26Z", result);
		};

		TEST_METHOD(UT_G2_W01)
		{
			Logger::WriteMessage("Whitebox - new line value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "\n" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("0", result);
		};

		TEST_METHOD(UT_G2_W02)
		{
			Logger::WriteMessage("Whitebox - Null value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "\0" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("0", result);
		};

		TEST_METHOD(UT_G2_W03)
		{
			Logger::WriteMessage("Whitebox - lowercase value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "3b" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("3B", result);
		};

		TEST_METHOD(UT_G2_W04)
		{
			Logger::WriteMessage("Whitebox - speical character value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "10#" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("10#", result);
		};

		TEST_METHOD(UT_G2_W05)
		{
			Logger::WriteMessage("Whitebox - one special character and one alphabet");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "!C" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("0C", result);
		};

		TEST_METHOD(UT_G2_W06)
		{
			Logger::WriteMessage("Whitebox - two alphabet character");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "BB" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("0B", result);
		};

		TEST_METHOD(UT_G2_W07)
		{
			Logger::WriteMessage("Whitebox - zero value");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "0E" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("0E", result);
		};

		TEST_METHOD(UT_G2_W08)
		{
			Logger::WriteMessage("Whitebox - Out of map range");

			// *** Parameters to be initialized for the testing to work ***
			char result[4] = { '\0' };

			// *** Parameters to be inputted ***
			char* dest = { "99G" };
			struct Point point;

			// *** Integration test logic ***
			point = convertStrToPoint(dest);
			strcpy_s(result, convertPointToStr(&point));

			// *** Test results ***
			Assert::AreEqual("99G", result);
		};

		TEST_METHOD(UT_G3_B01)
		{
			Logger::WriteMessage("Blackbox - To test if the destination is just next to the route, i.e. no diversion");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 11, 10 };
			struct Point target = { 11, 11 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("12K, 12L", res);
		};

		TEST_METHOD(UT_G3_B02)
		{
			Logger::WriteMessage("Blackbox - To test if the destination requires a simple diversion to a nearby point.");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 17, 10 };
			struct Point target = { 17, 8 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("18K, 18J, 18I", res);
		};

		TEST_METHOD(UT_G3_B03)
		{
			Logger::WriteMessage("Blackbox - To test if the destination requires a diversion around obstacles on the route.");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 10, 9 };
			struct Point target = { 12, 7 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("11J, 12I, 13H", res);
		};

		TEST_METHOD(UT_G3_B04)
		{
			Logger::WriteMessage("Blackbox - No diversion needed, destination is on the route.");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 4, 3 };
			struct Point target = { 4, 4 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("5D, 5E", res);
		};

		TEST_METHOD(UT_G3_B05)
		{
			Logger::WriteMessage("Blackbox - Shortest diversion possible with multiple choices");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 9, 3 };
			struct Point target = { 12, 6 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("10D, 11E, 12F, 13G", res);
		};

		TEST_METHOD(UT_G3_B06)
		{
			Logger::WriteMessage("Blackbox - Diversion start point is not connected to the route");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 0, 1 };
			struct Point target = { 1, 2 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("1B, 2C", res);
		};

		TEST_METHOD(UT_G3_B07)
		{
			Logger::WriteMessage("Blackbox - Diversion and target points are the same");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 7, 3 };
			struct Point target = { 7, 3 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("8D, 8D", res);
		};

		TEST_METHOD(UT_G3_B08)
		{
			Logger::WriteMessage("Blackbox - Target point is not on the route and unreachable");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 25, 1 };
			struct Point target = { 24, 1 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("26B, 25B", res);
		};

		TEST_METHOD(UT_G3_B09)
		{
			Logger::WriteMessage("Blackbox - Target point is unreachable");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 19, 9 };
			struct Point target = { 25, 9 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("20J, 21J, 22J, 23J, 24J, 25J, 26J", res);
		};

		TEST_METHOD(UT_G3_B10)
		{
			Logger::WriteMessage("Blackbox - Starting point is one of the target point");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 1, 1 };
			struct Point target = { 1, 2 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("2B, 2C", res);
		};

		TEST_METHOD(UT_G3_B11)
		{
			Logger::WriteMessage("Blackbox - Start point and target point are unreachable");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 25, 1 };
			struct Point target = { 26, 1 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("26B, 27B", res);
		};

		TEST_METHOD(UT_G3_W01)
		{
			Logger::WriteMessage("Whitebox - To test if the start point is NULL");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { NULL, NULL };
			struct Point target = { 0, 0 };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("1A, 1A", res);
		};

		TEST_METHOD(UT_G3_W02)
		{
			Logger::WriteMessage("Blackbox - Starting point is one of the target point");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { 0, 0 };
			struct Point target = { NULL, NULL };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("1A, 1A", res);
		};

		TEST_METHOD(UT_G3_W03)
		{
			Logger::WriteMessage("Blackbox - Starting point is one of the target point");

			// *** Parameters to be initialized for the testing to work ***
			struct Map routeMap = populateMap();
			struct Route testDiv = { {0,0},0,0 };
			char res[MAX_ROUTE * (MAX_DEST_LEN + 2)] = { '\0' };

			// *** Parameters to be inputted ***
			struct Point diversionStartPoint = { NULL, NULL };
			struct Point target = { NULL, NULL };

			// *** Integration test logic ***
			testDiv = shortestPath(&routeMap, diversionStartPoint, target);
			strcpy_s(res, listShortestDiversion(&testDiv));

			// *** Test results ***;
			Assert::AreEqual("1A, 1A", res);
		};
	};
}