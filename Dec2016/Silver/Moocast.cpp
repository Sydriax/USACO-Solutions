#include <fstream>
#include <queue>
#include <algorithm>
#include <math.h>

struct Cow {
	int x, y, p;
};
std::istream & operator>>(std::istream & i, Cow & c) {
	i >> c.x >> c.y >> c.p;
	return i;
}

inline bool canTalk(const Cow & c1, const Cow & c2) {
	int dx = c2.x - c1.x, dy = c2.y - c1.y;
	double dist = sqrt(dx * dx + dy * dy);
	return dist <= c1.p;
}

int main() {
	std::ifstream in("moocast.in");
	int numCows;
	in >> numCows;
	std::vector<Cow> cows(numCows);
	for(int i = 0; i < numCows; i++) in >> cows[i];
	in.close();
	std::vector< std::vector<bool> > connections(numCows, std::vector<bool>(numCows));
	for(int i = 0; i < numCows; i++) for(int j = 0; j < numCows; j++) connections[i][j] = canTalk(cows[i], cows[j]);
	int max = 0;
	for(int i = 0; i < numCows; i++) {
		std::vector<bool> visited(numCows, false);
		std::queue<int> toVisit;
		toVisit.push(i);
		visited[i] = true;
		while(!toVisit.empty()) {
			int k = toVisit.front();
			for(int j = 0; j < numCows; j++) if(!visited[j] && connections[k][j]) {
				toVisit.push(j);
				visited[j] = true;
			}
			toVisit.pop();
		}
		int num = std::count(visited.begin(), visited.end(), true);
		if(num > max) max = num;
		if(max == numCows) break;
	}
	std::ofstream out("moocast.out");
	out << max;
	out.flush();
	out.close();
	return 0;
}