#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
using json = nlohmann::json;

int main() {
	json l;
	ifstream map_file("osm.json", ifstream::binary);
	ofstream raw("raw_edges.json");
	map_file >> l;
	json r = {};
	for (auto i : l["features"]) {
		auto f = i["properties"];
		if (f.find("highway") != f.end() && f["highway"] == "primary") r+=i["geometry"]["coordinates"];
	}
	raw << r << endl;
	return 0;
}
