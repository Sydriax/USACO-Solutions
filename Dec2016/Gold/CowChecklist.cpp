#include <fstream>
#include <vector>
#include <map>
#include <iostream>

struct Cow {
	int x, y;
};
std::istream & operator>>(std::istream & i, Cow & c) {
	i >> c.x >> c.y;
	return i;
}
inline int getCost(const Cow & c1, const Cow & c2) {
	int dx = c1.x - c2.x, dy = c1.y - c2.y;
	return dx * dx + dy * dy;
}

int nh, ng, hgmult;
std::vector< std::vector<int> > hhCosts;
std::vector< std::vector<int> > hgCosts;
std::vector< std::vector<int> > ggCosts;
std::vector<long long> cache;

inline int index(const std::pair<bool, std::pair<int, int> > & pos) {
	return pos.first ? hgmult + pos.second.first * (ng + 1) + pos.second.second + 1 : pos.second.first * (ng + 1) + pos.second.second + 1;
}

long long getTotal(const std::pair<bool, std::pair<int, int> > pos) {
	if(cache[index(pos)] == -1) {
		if(pos.second.first == nh - 1) {
			if(pos.first)
				cache[index(pos)] = getTotal({ false, { pos.second.first, pos.second.second + 1 } }) + hgCosts[pos.second.first][pos.second.second + 1];
			else
				cache[index(pos)] = getTotal({ false, { pos.second.first, pos.second.second + 1 } }) + ggCosts[pos.second.second][pos.second.second + 1];
		}
		else if(pos.second.second == ng - 1) {
			if(pos.first)
				cache[index(pos)] = getTotal({ true, { pos.second.first + 1, pos.second.second } }) + hhCosts[pos.second.first][pos.second.first + 1];
			else
				cache[index(pos)] = getTotal({ true, { pos.second.first + 1, pos.second.second } }) + hgCosts[pos.second.first + 1][pos.second.second];
		}
		else if(pos.first) {
			cache[index(pos)] = std::min(getTotal({ true, { pos.second.first + 1, pos.second.second } }) + hhCosts[pos.second.first][pos.second.first + 1],
				getTotal({ false, { pos.second.first, pos.second.second + 1 } }) + hgCosts[pos.second.first][pos.second.second + 1]);
		}
		else {
			cache[index(pos)] = std::min(getTotal({ false, { pos.second.first, pos.second.second + 1 } }) + ggCosts[pos.second.second][pos.second.second + 1],
				getTotal({ true, { pos.second.first + 1, pos.second.second } }) + hgCosts[pos.second.first + 1][pos.second.second]);
		}
	}
	return cache[index(pos)];
}

int main() {
	std::fstream in("checklist.in");
	in >> nh >> ng;
	hgmult = (nh + 1) * (ng + 1) + 2;
	cache = std::vector<long long>(index({ true,  { nh - 1, ng - 1 } }) + 2, -1);
	cache[index({ true,  { nh - 1, ng - 1 } })] = 0; //Last pos
	cache[index({ false, { nh - 1, ng - 1 } })] = 9000000000000000000; //Last pos.
	std::vector<Cow> hCows(nh);
	std::vector<Cow> gCows(ng);
	for(int i = 0; i < nh; i++) in >> hCows[i];
	for(int i = 0; i < ng; i++) in >> gCows[i];
	hhCosts = std::vector< std::vector<int> >(nh, std::vector<int>(nh));
	for(int i = 0; i < nh; i++) for(int j = 0; j < nh; j++) hhCosts[i][j] = getCost(hCows[i], hCows[j]);
	hgCosts = std::vector< std::vector<int> >(nh, std::vector<int>(ng));
	for(int i = 0; i < nh; i++) for(int j = 0; j < ng; j++) hgCosts[i][j] = getCost(hCows[i], gCows[j]);
	ggCosts = std::vector< std::vector<int> >(ng, std::vector<int>(ng));
	for(int i = 0; i < ng; i++) for(int j = 0; j < ng; j++) ggCosts[i][j] = getCost(gCows[i], gCows[j]);
	std::ofstream out("checklist.out");
	out << getTotal({ true, { 0, -1 } });
	out.close();
}