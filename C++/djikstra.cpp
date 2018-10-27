// 30517 microseconds to find.
#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
#include <chrono>

using json = nlohmann::json;
using namespace std::chrono;
using namespace std;
typedef pair<double, int> di;
typedef vector<int> vi;
double inf = 1 << 30;

map<int, vector<di> > AdjList;
json v, e;

void djikstra(int source) {
	ofstream SSSP("djikstra.json");
	ofstream SSSP2("djikstra_path.json");
	priority_queue<di, vector<di>, greater<di> > q;
	vector<double> record (v.size(), inf);
	vector<int> p (v.size(), -1);
	q.push({0.0, source});
	record[source] = 0.0;
	while(!q.empty()) {
		auto t = q.top();
		q.pop();
		if (record[t.second] < t.first) continue;
		for (auto v : AdjList[t.second]) {
			if (record[v.second] > record[t.second] + v.first) {
				record[v.second] = record[t.second] + v.first;
				q.push({ record[v.second], v.second});
				p[v.second] = t.second;
			}
		}
	}
	json res;
	for (auto i : record) res += i;
	SSSP << setw(4) << res;
	json path;
	for (auto i : p) path += i;
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
    djikstra(3201);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    printf("Djikstra's take %lli microseconds to converge\n", duration);
	return 0;
}