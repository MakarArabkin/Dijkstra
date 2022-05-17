#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <limits.h>
#include <list>
using namespace std;

class CityPrice {
public:
    string city;
    int price;
    CityPrice(string city, int price);
};

CityPrice::CityPrice(string cityName, int priceTo)
{
    city = cityName;
    price = priceTo;
}

class ListOfRates {
public:
    vector<CityPrice> availableCities;
};

class AdjLists {
public:
    vector<string> cityTable;
    vector<ListOfRates> adjLists;
    AdjLists(int numOfCities);
    void addEdge(int src, CityPrice cityPrice);
};

AdjLists::AdjLists(int numCities) {
    adjLists = vector<ListOfRates>(numCities);
}

void AdjLists::addEdge(int src, CityPrice cityPrice) {
    if (adjLists[src].availableCities.size() == 0)
        adjLists[src] = ListOfRates();
    adjLists[src].availableCities.push_back(cityPrice);
}

string readData(string path) {
    string data = "";
    string line;
    ifstream file(path);
    if (file.is_open())
        while (getline(file, line))
            data += line + "\n";
    file.close();
    return data;
}

vector<string> split(const string& str, char delim) {
    vector<string> result;
    istringstream iss(str);
    string item;
    while (getline(iss, item, delim))
        result.push_back(item);
    return result;
}

map<string, vector<map<string, int>>> getMapFormData(string data) {
    map <string, vector<map<string, int>>> adjList;
    vector<string> rates = split(data, '\n');
    for (string& rate : rates)
    {
        vector<string> words = split(rate, ';');
        map<string, int> cityToPrice;
        map<string, int> cityFromPrice;
        if (words.at(2) != "N/A") {
            cityToPrice[words.at(1)] = std::stoi(words.at(2));
            if (adjList.find(words.at(0)) == adjList.end()) {
                vector<map<string, int>> mapVector = { cityToPrice };
                adjList[words.at(0)] = mapVector;
            }
            else {
                adjList[words.at(0)].push_back(cityToPrice);
            }
        }

        if (words.at(3) != "N/A") {
            cityFromPrice[words.at(0)] = std::stoi(words.at(3));
            if (adjList.find(words.at(1)) == adjList.end()) {
                vector<map<string, int>> mapVector = { cityFromPrice };
                adjList[words.at(1)] = mapVector;
            }
            else {
                adjList[words.at(1)].push_back(cityFromPrice);
            }
        }
    }
    return adjList;
}

int getCityId(vector<string> cityTable, string city) {
    for (int i = 0; i < cityTable.size(); i++)
        if (cityTable[i] == city) return i;
}

CityPrice getCityPriceFromMap(map<string, int> cityPriceMap) {
    for (auto const& cityAndPrice : cityPriceMap) {
        CityPrice cityPrice(cityAndPrice.first, cityAndPrice.second);
        return cityPrice;
    }
}

AdjLists getAdjLists(string data) {
    vector<string> cityTable;
    vector<string> rates = split(data, '\n');
    map<string, vector<map<string, int>>> mapAdjLists = getMapFormData(data);
    for (auto const& cityList : mapAdjLists) cityTable.push_back(cityList.first);
    AdjLists adjLists(cityTable.size());
    for (auto const& cityList : mapAdjLists) {
        for (map<string, int> rate : cityList.second) {
            CityPrice cityPrice = getCityPriceFromMap(rate);
            adjLists.addEdge(getCityId(cityTable, cityList.first), cityPrice);
        }
    }
    adjLists.cityTable = cityTable;
    return adjLists;
}

map<string, int> dijkstra(AdjLists adjLists, string start, vector<int>& way) {
    vector <string> visited;
    map<string, int> lengths;
    if (!way.empty()) return lengths;
    int i = 0;

    for (string city : adjLists.cityTable) {
        lengths[city] = city == start ? 0 : INT_MAX;
        way.push_back(-1);
    }

    string cur = start;
    string cityWithMinPrice = "";
    while (visited.size() != adjLists.cityTable.size()) {
        visited.push_back(cur);
        int curCityId = getCityId(adjLists.cityTable, cur);
        for (CityPrice rate : adjLists.adjLists[curCityId].availableCities) {
            string city = rate.city;
            int price = rate.price;

            if (lengths[cur] + price < lengths[city]) {
                lengths[city] = lengths[cur] + price;
                int curCityIndex = getCityId(adjLists.cityTable, city);
                int prevCityIndexl = getCityId(adjLists.cityTable, cur);
                way[curCityIndex] = prevCityIndexl;
            }
        }
        int minPrice = INT_MAX;
        for (auto const& cityPrice : lengths) {
            if (cityPrice.second < minPrice
                && std::find(visited.begin(), visited.end(), cityPrice.first) == visited.end()) {
                cityWithMinPrice = cityPrice.first;
                minPrice = cityPrice.second;
            }
        }
        cur = cityWithMinPrice;
    }
    return lengths;
}

int getPrice(AdjLists adjLists, string start, string finish) {
    vector<int> way;
    map<string, int> lengths = dijkstra(adjLists, start, way);
    return lengths[finish];
}

vector<string> getWay(AdjLists adjLists, string start, string finish) {
    vector<string> wayToFinish;
    vector<int> way;
    map<string, int> lengths = dijkstra(adjLists, start, way);
    vector <string> cityTable = adjLists.cityTable;
    int finishId = getCityId(cityTable, finish);
    int startId = getCityId(cityTable, start);
    int cur = finishId;

    while (cur != startId) {
        wayToFinish.push_back(cityTable[cur]);
        cur = way[cur];
    }

    wayToFinish.push_back(start);
    std::reverse(wayToFinish.begin(), wayToFinish.end());
    return wayToFinish;
}


int main()
{
    setlocale(LC_ALL, "");
    string cityFrom, cityTo;
    cin >> cityFrom;
    cin >> cityTo;
    string data = readData("flights.txt");
    AdjLists adjLists = getAdjLists(data);
    vector<string> way = getWay(adjLists, cityFrom, cityTo);
    int price = getPrice(adjLists, cityFrom, cityTo);
    cout << "price is " << price << endl;
    cout << "path: " << endl;
    for (string city : way) cout << "       " << city << endl;
}
