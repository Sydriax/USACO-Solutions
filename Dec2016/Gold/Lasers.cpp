#include <fstream>
#include <list>
#include <unordered_set>

struct Loc {
	int x, y;
};
std::istream & operator>>(std::istream & i, Loc & l) {
	i >> l.x >> l.y;
	return i;
}

int main() {
	int n;
	Loc laser, barn, l;
	std::ifstream in("lasers.in");
	in >> n >> laser >> barn;
	std::list<Loc> posts(n);
	for(int i = 0; i < n; i++) {
		in >> l;
		posts.push_back(l);
	}
	in.close();
	std::unordered_set<int> rXs, rYs; //reachable Xs, Ys;
	rXs.insert(laser.x);
	rYs.insert(laser.y);
	int counter;
	for(counter = 0; rXs.count(barn.x) == 0 && rYs.count(barn.y) == 0 && !posts.empty(); counter++) {
		std::unordered_set<int> newXs, newYs;
		auto i = posts.begin();
		while(i != posts.end()) {
			if(rXs.count(i->x) || rYs.count(i->y)) {
				newXs.insert(i->x);
				newYs.insert(i->y);
				i = posts.erase(i);
			}
			else i++;
		}
		for(auto i = newXs.begin(); i != newXs.end(); i++) rXs.insert(*i);
		for(auto i = newYs.begin(); i != newYs.end(); i++) rYs.insert(*i);
	}
	std::ofstream out("lasers.out");
	out << (rXs.count(barn.x) || rYs.count(barn.y) ? counter : -1);
	out.close();
	return 0;
}