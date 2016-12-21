#include <fstream>
#include <algorithm>
#include <vector>

// Works on sorted array.
inline int findUp(const std::vector<int> & v, int i) {
	int upBound = v.size() - 1, lowBound = 0;
	while(true) {
		int mid = (upBound + lowBound) / 2;
		if(v[mid] == i) return mid;
		if(v[mid] > i) {
			if(upBound == mid) return upBound;
			upBound = mid;
		}
		else {
			if(lowBound == mid) return upBound;
			lowBound = mid;
		}
	}
}

int main() {
	std::ifstream in("haybales.in");
	std::ofstream out("haybales.out");
	int n, q;
	in >> n >> q;
	std::vector<int> vals(n);
	for(int i = 0; i < n; i++) in >> vals[i];
	vals.push_back(1000000001);
	std::sort(vals.begin(), vals.end());
	for(int i = 0; i < q; i++) {
		int j, k;
		in >> j >> k;
		int jLoc = findUp(vals, j);
		int kLoc = findUp(vals, k);
		if(vals[kLoc] > k) out << kLoc - jLoc;
		else out << 1 + kLoc - jLoc;
		if(i != q - 1) out << '\n';
	}
	out.flush();
	out.close();
	in.close();
	return 0;
}
