#include <iostream>

using namespace std;

int main()
{
    int n, f;

    cin >> n >> f;

    int h_length = 0;
    int h_indexes[100];

    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;

        if (c >= f)
            continue;

        h_indexes[h_length] = i;
        h_length++;
    }

    for (int i = 0; i < h_length; i++) {
        for (int j = i + 1; j < h_length; j++) {
            if (h_indexes[i] <= h_indexes[j])
                continue;

            int tmp = h_indexes[i];
            h_indexes[i] = h_indexes[j];
            h_indexes[j] = tmp;
        }
    }

    for (int i = 0; i < h_length; i++) {
        cout << h_indexes[i] << " ";
    }
}
