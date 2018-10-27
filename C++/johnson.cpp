#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
using json = nlohmann::json;
using namespace std;
typedef pair<double, int> di;
typedef vector<int> vi;
double inf = 1 << 30;

map<int, vector<di> > AdjList;
json v, e;
vector<double> Gprime;
vector<vector<double> > APSP;

void djikstra(int source) {
	priority_queue<di, vector<di>, greater<di> > q;
	vector<double> G(v.size(), inf);
	q.push({0.0, source});
	G[source] = 0.0;
	while(!q.empty()) {
		auto t = q.top();
		q.pop();
		if (G[t.second] < t.first) continue;
		for (auto v : AdjList[t.second]) {
			if (v.second == v.size()) continue;
			if (G[v.second] > G[t.second] + v.first) {
				G[v.second] = G[t.second] + v.first;
				q.push({ G[v.second], v.second});
			}
		}
	}
	APSP.push_back(G);
}

void bellmanford(int source) {
	Gprime.assign(v.size() + 1, inf);
	vector<int> par(v.size() + 1, -1);
	dist[source] = 0.0;
	for (int i = 1; i < v.size(); i++) {
		for (auto ed : e) {
			if (dist[ed[1]] > dist[ed[0]] + double(ed[2])) {
				dist[ed[1]] = dist[ed[0]] + double(ed[2]);
				par[ed[1]] = ed[0];
			}
		}
	}
}

void johnson() {
	//adding addition source s to the graph
	int source = v.size();
	for (int i = 0; i < source; i++) {
		AdjList[source].push_back({ 0.0, i });
		AdjList[i].push_back({ 0.0, source});
	}
	bellmanford(source);
	//computing new edge cost
	for (auto&i : AdjList) {
		if (i.first == source) continue;
		for (auto& j : i.second) {
			if (j.second == source) continue;
			j.first+= Gprime[i.first] - Gprime[j.second];
		}
	}
	
	for (int i = 0; i < source; i++) {
		djikstra(i);
	}

	for (int i = 0; i < source; i++) {
		for (int j = 0; j < source; j++) {
			APSP[i][j] += Gprime[j] - Gprime[i];
		}
	}
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
	johnson();
	return 0;
}