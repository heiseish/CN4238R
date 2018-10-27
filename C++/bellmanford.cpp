//274010629 microseconds to converge
#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
#include <chrono>

using namespace std::chrono;
using json = nlohmann::json;
using namespace std;
typedef pair<double, int> di;
typedef vector<int> vi;
double inf = 1 << 30;

map<int, vector<di> > AdjList;
json v, e;

void bellmanford(int source) {
	ofstream SSSP("bellmanford.json");
	vector<double> dist(v.size(), inf);
	vector<int> par(v.size(), -1);
	dist[source] = 0.0;
	for (int i = 1; i < v.size(); i++) {
		for (auto ed : e) {
			if (dist[ed[1]] > dist[ed[0]] + double(ed[2])) {
				dist[ed[1]] = dist[ed[0]] + double(ed[2]);
				par[ed[1]] = ed[0];
			}
		}
	}
	json res;
	for (auto i : dist) res += i;
	SSSP << setw(4) << res;

	ofstream SSSP2("bellmanford_path.json");
	json path;
	for (auto i : par) path += i;
	SSSP2 << setw(4) << path;
}

int main() {
	ifstream vertices("vertices.json", ifstream::binary);
	ifstream edges("edges.json", ifstream::binary);
	vertices >> v;
	edges >> e;
	for (auto i : e) {
		AdjList[i[0]].push_back({ i[2], i[1] });
		AdjList[i[1]].push_back({ i[2], i[0] });
	}
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
    bellmanford(3201);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    printf("Bellman Ford's take %lli microseconds to converge\n", duration);
	
	return 0;
}