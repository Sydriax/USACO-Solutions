#include <fstream>
#include <vector>
#include <set>
#include <map>

struct Cow {
	int x, y, index;
};
std::istream & operator>>(std::istream & i, Cow & c) {
	i >> c.x >> c.y;
	return i;
}
inline int getCost(const Cow & c1, const Cow & c2) {
	int dx = c1.x - c2.x, dy = c1.y - c2.y;
	return dx * dx + dy * dy;
}

int main() {
	std::fstream in("moocast.in");
	int numCows;
	in >> numCows;
	std::vector<Cow * > cows(numCows);
	std::vector< std::set<Cow * > * > barns;
	std::map<int, std::set<Cow * > * > nsa; // Keeping tabs on all the cattle.
	for(int i = 0; i < numCows; i++) {
		cows[i] = (Cow * )malloc(sizeof(Cow));
		in >> *cows[i];
		cows[i]->index = i;
		barns.push_back(new std::set<Cow * >());
		barns.back()->insert(cows[i]);
		nsa[i] = barns.back();
	}
	in.close();
	std::vector< std::vector<int> > costs(numCows, std::vector<int>(numCows));
	for(int i = 0; i < numCows; i++) for(int j = 0; j < numCows; j++) costs[i][j] = getCost(*cows[i], *cows[j]);
	int maxCost = 0;
	while(barns.size() > 1) {
		std::set<Cow * > * toMerge = barns.back();
		barns.pop_back();
		int lowest = -1, lowestVal = 1250000001;
		for(auto i = toMerge->begin(); i != toMerge->end(); i++) {
			for(auto j = cows.begin(); j != cows.end(); j++) if(toMerge->count(*j) == 0) {
				int val = costs[(*i)->index][(*j)->index];
				if(val < lowestVal) {
					lowestVal = val;
					lowest = (*j)->index;
				}
			}
		}
		if(lowestVal > maxCost) maxCost = lowestVal;
		std::set<Cow * > * mergeInto = nsa[lowest];
		for(auto i = toMerge->begin(); i != toMerge->end(); i++) {
			nsa[(*i)->index] = mergeInto;
			mergeInto->insert(*i);
		}
		delete toMerge;
	}
	delete barns.front();
	for(auto i = cows.begin(); i != cows.end(); i++) delete *i;
	std::ofstream out("moocast.out");
	out << maxCost;
	out.close();
}