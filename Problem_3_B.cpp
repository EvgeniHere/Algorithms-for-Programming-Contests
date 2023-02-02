#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;
vector<int> comic_moods;
vector<int> best_moods;
int max_n;

int calculate_best_mood(int n) {
    if (n == 0)
        return -100 + comic_moods[0];

    int erg = calculate_best_mood(n - 1);

}

int main() {
    cin >> max_n;

    vector<int> tmp_comic_moods(max_n);
    vector<int> tmp_best_moods(max_n);

    for (int i = 0; i < max_n; i++)
        cin >> tmp_comic_moods[i];

    comic_moods = tmp_comic_moods;
    best_moods = tmp_best_moods;

    calculate_best_mood(0, true, -100);

    int x1 = best_moods[0] - 100;

    vector<int> tmp_best_moods2(max_n);
    best_moods = tmp_best_moods2;

    calculate_best_mood(1, true, -100);

    int x2 = best_moods[0] - 100;

    cout << max(x1, x2) << endl;
}
