#include <fstream>
#include <map>
inline std::pair<int, int> splitLine(const std::string & line) {
	int spaceLoc = line.find_first_of(' ');
	return { line[spaceLoc + 1] * 256 + line[spaceLoc + 2], line[0] * 256 + line[1] };
}
int main() {
	std::ifstream in("citystate.in");
	int row;
	std::string line;
	(in >> row).get(); //Removes newline.
	std::ofstream out("citystate.out");
	std::map<int, std::map<int, int> > states;
	int counter = 0;
	for(int i = 0; i < row; i++) {
		std::getline(in, line);
		auto pair = splitLine(line);
		if(states.count(pair.first) == 0) states[pair.first] = std::map<int, int>();
		if(states[pair.first].count(pair.second) == 0) states[pair.first][pair.second] = 0;
		states[pair.first][pair.second]++;
	}
	for(auto a = states.begin(); a != states.end(); a++) {
		int aComp = a->first;
		for(auto b = a; b != states.end(); b++) if(a->first != b->first) {
			int bComp = b->first;
			if(a->second.count(bComp) && b->second.count(aComp)) {
				counter += (a->second[bComp] * b->second[aComp]);
			}
		}
	}
	out << counter;
	out.flush();
	out.close();
	in.close();
}