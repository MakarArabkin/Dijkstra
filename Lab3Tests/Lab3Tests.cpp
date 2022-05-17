#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3/Dijkstra.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3Tests
{
	TEST_CLASS(Lab3Tests)
	{

	public:

		TEST_METHOD(getAddjListsTest)
		{
			string data = "�����-���������;������;10;20\n������;���������;40;35\n�����-���������;���������;14;N/A\n�����������;���������;10;8\n�����������;�����-���������;N/A;3\n";
			AdjLists actualAdjList = getAdjLists(data);
			Assert::IsTrue(actualAdjList.cityTable.size() == 4);
			Assert::IsTrue(actualAdjList.adjLists[0].availableCities.size() == 1);
		}

		TEST_METHOD(getCityIdTest)
		{
			vector<string> cityTable = { "������", "�����-���������", "���������" };
			int actualCityId = getCityId(cityTable, "�����-���������");
			Assert::AreEqual(actualCityId, 1);
		}

		TEST_METHOD(dijkstraTest)
		{
			string data = "�����-���������;������;10;20\n������;���������;40;35\n�����-���������;���������;14;N/A\n�����������;���������;10;8\n�����������;�����-���������;N/A;3\n";
			AdjLists adjList = getAdjLists(data);
			string start = "������";
			vector<int> way;
			map<string, int>  prices = dijkstra(adjList, start, way);
			Assert::AreEqual(prices["�����-���������"], 20);
			Assert::AreEqual(prices["���������"], 33);
		}

		TEST_METHOD(getPriceTest)
		{
			string data = "�����-���������;������;10;20\n������;���������;40;35\n�����-���������;���������;14;N/A\n�����������;���������;10;8\n�����������;�����-���������;N/A;3\n";
			AdjLists adjList = getAdjLists(data);
			string start = "������";
			string finish = "���������";
			int  actualPrices = getPrice(adjList, start, finish);
			Assert::AreEqual(actualPrices, 33);
		}

		TEST_METHOD(CityPriceTest)
		{
			CityPrice actualCityPrice("������", 132);
			string expectedCity = "������";
			Assert::IsTrue(actualCityPrice.city == expectedCity);
			Assert::IsTrue(actualCityPrice.price == 132);
		}

		TEST_METHOD(getWayTest)
		{
			string data = "�����-���������;������;10;20\n������;���������;40;35\n�����-���������;���������;14;N/A\n�����������;���������;10;8\n�����������;�����-���������;N/A;3\n";
			AdjLists adjList = getAdjLists(data);
			string start = "������";
			string finish = "���������";
			vector<string> actualWay = getWay(adjList, start, finish);
			vector<string> expectedWay = { "������", "�����-���������", "�����������", "���������" };
			Assert::IsTrue(actualWay == expectedWay);
		}

		TEST_METHOD(splitTwoParamTest)
		{
			vector<string> expectedSplit = { "�����-���������", "������", "���������" };
			vector<string> actualSplit = split("�����-���������;������;���������", ';');
			Assert::IsTrue(actualSplit == expectedSplit);
		}

		TEST_METHOD(addEdgeTest)
		{
			string data = "�����-���������;������;10;20\n������;���������;40;35\n�����-���������;���������;14;N/A\n�����������;���������;10;8\n�����������;�����-���������;N/A;3\n";
			AdjLists adjList = getAdjLists(data);
			CityPrice cityPrice("������", 43);
			adjList.addEdge(0, cityPrice);
			Assert::IsTrue(adjList.adjLists[0].availableCities[1].city == "������");
			Assert::IsTrue(adjList.adjLists[0].availableCities[1].price == 43);
		}

		TEST_METHOD(AdjListsTest)
		{
			string data = "�����-���������;������;10;20\n������;���������;40;35\n�����-���������;���������;14;N/A\n�����������;���������;10;8\n�����������;�����-���������;N/A;3\n";
			AdjLists adjLists(5);
			Assert::IsTrue(adjLists.adjLists.size() == 5);
		}

		TEST_METHOD(getCityPriceFromMapTest)
		{
			map<string, int> cityPriceMap;
			cityPriceMap["������"] = 132;
			CityPrice actualCityPrice = getCityPriceFromMap(cityPriceMap);
			Assert::IsTrue(actualCityPrice.city == "������");
			Assert::IsTrue(actualCityPrice.price == 132);
		}

	};
}

