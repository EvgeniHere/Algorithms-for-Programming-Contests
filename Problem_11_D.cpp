// Problem_11_D.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class vec2 {
	int x;
	int y;

public:
	vec2() {
		x = -1;
		y = -1;
	}

	vec2(int myx, int myy) {
		x = myx;
		y = myy;
	}

	vec2 sub(vec2 other) {
		return vec2(x - other.x, y - other.y);
	}

	bool isParallel(vec2 otherDir) {
		return x * otherDir.y - otherDir.x * y == 0;
	}

	bool isZero() {
		return x == 0 && y == 0;
	}
};

class line {
	vec2 start;
	vec2 end;
	vec2 dir;

public:
	line(vec2 a, vec2 b) {
		start = a;
		end = b;
		dir = end.sub(start);
	}

	bool isParallel(line other) {
		return dir.isParallel(other.dir);
	}

	bool isSame(line other) {
		if (!isParallel(other)) return false;

		vec2 newdir = other.start.sub(start);
		if (newdir.isZero()) newdir = other.start.sub(end);

		return newdir.isParallel(dir);
	}
};

int main() {
	int w;
	int n;

	cin >> w >> n;

	vector<line> lines;

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		vec2 start = vec2(x, y);
		cin >> x >> y;
		vec2 end = vec2(x, y);

		line tmp_line = line(start, end);

		bool addLine = true;
		for (int j = 0; j < lines.size(); j++) {
			if (tmp_line.isSame(lines[j])) {
				addLine = false;
				break;
			}
		}

		if (addLine) lines.push_back(tmp_line);
	}

	bool allParallel = true;
	for (int i = 1; i < lines.size(); i++) {
		if (!lines[0].isParallel(lines[i])) {
			allParallel = false;
			break;
		}
	}

	int cur = 0, add = 0;
	if (allParallel) {
		cur = lines.size() + 1;
		add = cur;
	} else {
		cur = 2 * lines.size();
		add = 2;
	}

	int res = 0;

	if (add < 2) add = 2;

	while (cur < w) {
		res++;
		cur += add;
		add = 2;
	}

	cout << res << endl;
}
