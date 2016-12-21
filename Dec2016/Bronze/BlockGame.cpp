#include <fstream>
#include <array>
#include <algorithm>
#include <string>
#include <iostream>
typedef std::array<int, 26> Alphabet;
Alphabet & operator+=(Alphabet & a1, const Alphabet & a2) {
	for(int i = 0; i < 26; i++) a1[i] += a2[i];
	return a1;
}
Alphabet operator|(const Alphabet & a1, const Alphabet & a2) {
	Alphabet answer;
	for(int i = 0; i < 26; i++) answer[i] = std::max(a1[i], a2[i]);
	return answer;
}
Alphabet getAlphabet(const std::string & s) {
	Alphabet answer;
	for(int i = 0; i < 26; i++) answer[i] = std::count(s.begin(), s.end(), 'a' + i);
	return answer;
}
std::ostream & operator<<(std::ostream & o, const Alphabet & a) {
	for(int i = 0; i < 26; i++) o << a[i] << '\n';
	return o;
}
int main() {
	std::ifstream in("blocks.in");
	Alphabet total;
	for(int i = 0; i < 26; i++) total[i] = 0;
	int blockCount;
	in >> blockCount;
	std::string line;
	std::getline(in, line); // Flush newline.
	for(int i = 0; i < blockCount; i++) {
		std::getline(in, line);
		int spaceIndex = line.find_first_of(' ');
		total += (getAlphabet(line.substr(0, spaceIndex)) | getAlphabet(line.substr(spaceIndex + 1)));
	}
	in.close();
	std::ofstream out("blocks.out");
	out << total;
	out.flush();
	out.close();
	return 0;
}