#include <bits/stdc++.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

typedef pair<int, int> ii;
typedef pair<double, ii> dii;
vector<int> d;


double calculateDist(json f, json s) {
	double x1 = f[0], y1 = f[1];
	double x2 = s[0], y2 = s[1];
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int find(int index) {
	if (d[index] == -1) return index;
	return d[index] = find(d[index]);
}

bool join(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b) return false;
	d[a] = b;
	return true;
}
int main() {
	json v;
	ifstream vertices("vertices.json", ifstream::binary);
	vertices >> v;
	// priority_queue<dii, vector<dii>, greater<dii> > heap;
	d.assign(v.size(), -1);
	vector<dii> heap;
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			double dist = calculateDist(v[i], v[j]);
			heap.push_back({ dist, { i, j}});
		}
	}
	sort(heap.begin(), heap.end());
	int k = 10, s = v.size(), i = 0;
	while (s != k) {
		dii temp = heap[i++];
		if (join(temp.second.first, temp.second.second)) s--;
	}
	unordered_map<int, vector<int> > clusters;
	for (int i = 0; i < v.size(); i++) {
		if (d[i] == -1) clusters[i].push_back(i);
		else clusters[find(i)].push_back(i);
	}
	json res;
	ofstream clsters("clusters.json");
	for (auto i : clusters) res += i.second;
	clsters << setw(4) << res << endl;

	return 0;
}