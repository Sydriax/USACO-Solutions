#include <fstream>
struct Point {
	int x, y;
};
std::istream & operator>>(std::istream & i, Point & p) {
	i >> p.x >> p.y;
	return i;
}
int main() {
	Point ll1, ur1, ll2, ur2;
	std::ifstream in("square.in");
	in >> ll1 >> ur1 >> ll2 >> ur2;
	in.close();
	Point min = { std::min(ll1.x, ll2.x), std::min(ll1.y, ll2.y) };
	Point max = { std::max(ur1.x, ur2.x), std::max(ur1.y, ur2.y) };
	int max_dim = std::max(max.x - min.x, max.y - min.y);
	std::ofstream out("square.out");
	out << max_dim * max_dim;
	out.flush();
	out.close();
	return 0;
}