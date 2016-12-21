#include <fstream>
#include <string>
int main() {
	std::ifstream in("cowsignal.in");
	int row, col, amp;
	std::string line, outLine;
	(in >> row >> col >> amp).get(); //Removes newline.
	std::ofstream out("cowsignal.out");
	for(int i = 0; i < row; i++) {
		std::getline(in, line);
		outLine.clear();
		for(auto j = line.begin(); j != line.end(); j++) for(int k = 0; k < amp; k++) outLine += *j;
		if(i < row - 1) for(int k = 0; k < amp; k++) out << outLine << '\n';
		else {
			for(int k = 0; k < amp - 1; k++) out << outLine << '\n';
			out << outLine;
		}
	}
	in.close();
	out.flush();
	out.close();
	return 0;
}