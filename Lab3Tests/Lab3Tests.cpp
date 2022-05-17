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
			string data = "Санкт-Петербург;Москва;10;20\nМосква;Хабаровск;40;35\nСанкт-Петербург;Хабаровск;14;N/A\nВладивосток;Хабаровск;10;8\nВладивосток;Санкт-Петербург;N/A;3\n";
			AdjLists actualAdjList = getAdjLists(data);
			Assert::IsTrue(actualAdjList.cityTable.size() == 4);
			Assert::IsTrue(actualAdjList.adjLists[0].availableCities.size() == 1);
		}

		TEST_METHOD(getCityIdTest)
		{
			vector<string> cityTable = { "Москва", "Санкт-Петербург", "Хабаровск" };
			int actualCityId = getCityId(cityTable, "Санкт-Петербург");
			Assert::AreEqual(actualCityId, 1);
		}

		TEST_METHOD(dijkstraTest)
		{
			string data = "Санкт-Петербург;Москва;10;20\nМосква;Хабаровск;40;35\nСанкт-Петербург;Хабаровск;14;N/A\nВладивосток;Хабаровск;10;8\nВладивосток;Санкт-Петербург;N/A;3\n";
			AdjLists adjList = getAdjLists(data);
			string start = "Москва";
			vector<int> way;
			map<string, int>  prices = dijkstra(adjList, start, way);
			Assert::AreEqual(prices["Санкт-Петербург"], 20);
			Assert::AreEqual(prices["Хабаровск"], 33);
		}

		TEST_METHOD(getPriceTest)
		{
			string data = "Санкт-Петербург;Москва;10;20\nМосква;Хабаровск;40;35\nСанкт-Петербург;Хабаровск;14;N/A\nВладивосток;Хабаровск;10;8\nВладивосток;Санкт-Петербург;N/A;3\n";
			AdjLists adjList = getAdjLists(data);
			string start = "Москва";
			string finish = "Хабаровск";
			int  actualPrices = getPrice(adjList, start, finish);
			Assert::AreEqual(actualPrices, 33);
		}

		TEST_METHOD(CityPriceTest)
		{
			CityPrice actualCityPrice("Москва", 132);
			string expectedCity = "Москва";
			Assert::IsTrue(actualCityPrice.city == expectedCity);
			Assert::IsTrue(actualCityPrice.price == 132);
		}

		TEST_METHOD(getWayTest)
		{
			string data = "Санкт-Петербург;Москва;10;20\nМосква;Хабаровск;40;35\nСанкт-Петербург;Хабаровск;14;N/A\nВладивосток;Хабаровск;10;8\nВладивосток;Санкт-Петербург;N/A;3\n";
			AdjLists adjList = getAdjLists(data);
			string start = "Москва";
			string finish = "Хабаровск";
			vector<string> actualWay = getWay(adjList, start, finish);
			vector<string> expectedWay = { "Москва", "Санкт-Петербург", "Владивосток", "Хабаровск" };
			Assert::IsTrue(actualWay == expectedWay);
		}

		TEST_METHOD(splitTwoParamTest)
		{
			vector<string> expectedSplit = { "Санкт-Петербург", "Москва", "Хабаровск" };
			vector<string> actualSplit = split("Санкт-Петербург;Москва;Хабаровск", ';');
			Assert::IsTrue(actualSplit == expectedSplit);
		}

		TEST_METHOD(addEdgeTest)
		{
			string data = "Санкт-Петербург;Москва;10;20\nМосква;Хабаровск;40;35\nСанкт-Петербург;Хабаровск;14;N/A\nВладивосток;Хабаровск;10;8\nВладивосток;Санкт-Петербург;N/A;3\n";
			AdjLists adjList = getAdjLists(data);
			CityPrice cityPrice("Москва", 43);
			adjList.addEdge(0, cityPrice);
			Assert::IsTrue(adjList.adjLists[0].availableCities[1].city == "Москва");
			Assert::IsTrue(adjList.adjLists[0].availableCities[1].price == 43);
		}

		TEST_METHOD(AdjListsTest)
		{
			string data = "Санкт-Петербург;Москва;10;20\nМосква;Хабаровск;40;35\nСанкт-Петербург;Хабаровск;14;N/A\nВладивосток;Хабаровск;10;8\nВладивосток;Санкт-Петербург;N/A;3\n";
			AdjLists adjLists(5);
			Assert::IsTrue(adjLists.adjLists.size() == 5);
		}

		TEST_METHOD(getCityPriceFromMapTest)
		{
			map<string, int> cityPriceMap;
			cityPriceMap["Москва"] = 132;
			CityPrice actualCityPrice = getCityPriceFromMap(cityPriceMap);
			Assert::IsTrue(actualCityPrice.city == "Москва");
			Assert::IsTrue(actualCityPrice.price == 132);
		}

	};
}

