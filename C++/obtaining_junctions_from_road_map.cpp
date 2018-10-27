/**
* Sparse graph
* 20458 vertices
* 20838 edges
*/
#include <nlohmann/json.hpp>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
using json = nlohmann::json;
typedef pair<int, int> ii;

double calculateDist(json f, json s) {
	double x1 = f[0], y1 = f[1];
	double x2 = s[0], y2 = s[1];
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
int main() {
	json l;
	ifstream raw_edges("raw_edges.json", ifstream::binary);
	ofstream vertices("vertices.json");
	ofstream edges("edges.json");
	vector<json> record;
	int current = 0;
	raw_edges >> l;
	json v = {}, e = {};
	for (auto i : l) {
		auto fi = i[0];
		if (fi[0].type() != json::value_t::number_float 
		&& fi[0].type() != json::value_t::number_integer) continue;
		if (find(record.begin(), record.end(), fi) == record.end()) record.push_back(fi);
		for (int j = 0; j < i.size() - 1; j++) {
			auto pi = i[j];
			auto ni = i[j + 1];
			if (ni[0].type() != json::value_t::number_float 
				&& ni[0].type() != json::value_t::number_integer) continue;
			if (find(record.begin(), record.end(), ni) == record.end()) record.push_back(ni);
			ptrdiff_t pos_a = find(record.begin(), record.end(), pi) - record.begin();
			ptrdiff_t pos_b = find(record.begin(), record.end(), ni) - record.begin();
			e += { pos_a, pos_b, calculateDist(pi, ni)};
		}
	}
	for (auto i : record) v += i;
	vertices << v << endl;
	edges << e << endl;
	return 0;
}
