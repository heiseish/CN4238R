/**
* Eusoff 1.294731, 103.7694386
* index: 3201
*/
#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
using json = nlohmann::json;
using namespace std;
int main() {
	double maxY = 1.302898, minY = 1.287827;
	double minX = 103.768938, maxX = 103.784681;
	ifstream vertices("vertices.json", ifstream::binary);
	json v, r;
	vertices >> v;
	for (int i = 0; i < v.size(); i++) {
		if (v[i][0] == 103.7694386 && v[i][1] == 1.294731) {
			printf("%d\n", i);
		}
		double x = i[0], y = i[1];
		if (y >= minY && y <= maxY && x >= minX && x <= maxX) r+=i;
	}
	ofstream nus("nus_points.json");
	nus << setw(4) << r << endl;
	return 0;
}