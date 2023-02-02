#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int INF = 100000000;

int n, m;
bool first;
vector<vector<int>> damage_map;
vector<vector<int>> best_hp_map;

int most_hp(int hp, int px, int py, int last_move) {
    if (px < 0 || px >= n || py < 0 || py >= m)
        return -INF;

    if (!first)
        hp -= damage_map[px][py];
    else
        first = false;

    if (px == 0)
        return hp;

    if (best_hp_map[px][py])
        return best_hp_map[px][py];

    int left_hp = -INF;
    int up_hp = -INF;
    int down_hp = -INF;

    left_hp = most_hp(hp, px - 1, py, 0);

    if (last_move != 1)
        up_hp = most_hp(hp, px, py - 1, -1);

    if (last_move != -1)
        down_hp = most_hp(hp, px, py + 1, 1);

    best_hp_map[px][py] = max(down_hp, max(up_hp, left_hp));

    return best_hp_map[px][py];
}

int main() {
    int t, h;
    cin >> n >> m >> t >> h;

    for (int i = 0; i < n; i++) {
        vector<int> damage_column(m);
        damage_map.push_back(damage_column);
        vector<int> hp_column(m);
        best_hp_map.push_back(hp_column);
    }

    for (int i = 0; i < t; i++) {
        int x, y, r, d;
        cin >> x >> y >> r >> d;

        x--;
        y--;

        for (int j = -r; j < r + 1; j++) {
            for (int k = -r; k < r + 1; k++) {
                if (x + j < 0 || y + k < 0 || x + j >= n || y + k >= m)
                    continue;

                damage_map[x + j][y + k] += d;
            }
        }
    }

    int max_hp = -INF;

    for (int i = 0; i < m; i++) {

        for (int i = 0; i < n; i++) {
            vector<int> hp_column(m);
            best_hp_map[i] = hp_column;
        }

        first = true;
        int cur_max_hp = most_hp(h, n - 1, i, 0);

        if (cur_max_hp > max_hp)
            max_hp = cur_max_hp;
    }

    if (max_hp < 0)
        max_hp = 0;

    std::cout << max_hp << endl;
}
