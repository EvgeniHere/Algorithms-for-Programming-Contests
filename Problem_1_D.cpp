#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;

    int cases_len[100];
    int cases_seq[100][2048];

    for (int i = 0; i < t; i++) {
        int N;
        cin >> N;
        cases_len[i] = N;

        for (int j = 0; j < N; j++) {
            cin >> cases_seq[i][j];
        }
    }

    for (int i = 0; i < t; i++) {
        for (int j = cases_len[i] - 1; j >= 0; j--) {
            cout << cases_seq[i][j] << " ";
        }

        cout << endl;
    }
}