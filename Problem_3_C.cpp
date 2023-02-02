#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;

vector<vector<int>> skiline_points;
vector<vector<int>> max_points;

int best_skiline(int x, int y) {
    if (y >= skiline_points.size())
        return 0;

    if (x > skiline_points[y].size())
        return -INF;

    if (max_points[y][x])
        return max_points[y][x];

    max_points[y][x] = max(best_skiline(x, y + 1), best_skiline(x + 1, y + 1)) + skiline_points[y][x];

    return max_points[y][x];
}

int main() {
    int max_x;

    cin >> max_x;

    vector<vector<int>> tmp_skiline_points;
    vector<vector<int>> tmp_max_points;

    for (int i = 0; i < max_x; i++) {
        vector<int> row(i + 1);
        vector<int> row2(i + 1);
        for (int j = 0; j <= i; j++)
            cin >> row[j];
        tmp_skiline_points.push_back(row);
        tmp_max_points.push_back(row2);
    }
    
    skiline_points = tmp_skiline_points;
    max_points = tmp_max_points;

    int sol = best_skiline(0, 0);

    cout << sol << endl;
}
