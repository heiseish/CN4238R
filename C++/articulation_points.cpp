#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
using namespace std;
using json = nlohmann::json;
typedef pair<double, int> di;
typedef vector<int> vi;

map<int, vector<int> > AdjList;
json v, e;
// array of articulation points. true if it is AP.
vector<bool> articulation_points;
vector<bool> explored;
vector<int> key;
vector<int> num;
vector<int> par;
vector<int> num_child;
int ct = 0;
void DFS(int source) {
	explored[source] = true;
	key[source] = num[source] = ct++;
	for (auto i : AdjList[source]) {
		if (!explored[i]) {
			num_child[source]++;
			par[i] = source;
			DFS(i);

			if (key[i] >= num[source]) articulation_points[source] = true;
			key[source] = min({ key[source], key[i]});
		} else if (par[source] != i) {
			key[source] = min({ key[source], num[i]});
		}
	}
}

void Tarjan() {
	int source = 0;
	DFS(source);
	if (num_child[source] >= 2) articulation_points[source] = true;
}

int main() {
	ifstream vertices("vertices.json", ifstream::binary);
	ifstream edges("edges.json", ifstream::binary);
	vertices >> v;
	edges >> e;
	for (auto i : e) {
		AdjList[i[0]].push_back(i[1]);
		AdjList[i[1]].push_back(i[0]);
	}
	articulation_points.assign(v.size(), false);
	explored.assign(v.size(), false);
	key.assign(v.size(), -1);
	num.assign(v.size(), -1);
	par.assign(v.size(), -1);
	num_child.assign(v.size(), 0);
	Tarjan();
	json res;
	json res2;
	for (int i = 0; i < v.size(); i++) {
		if (articulation_points[i]) res += v[i];
		else res2 += v[i];
	}
	ofstream articulation_points("articulation_points.json");
	articulation_points << setw(4) << res << endl;

	ofstream non_articulation_points("non_articulation_points.json");
	non_articulation_points << setw(4) << res2 << endl;
	return 0;
}