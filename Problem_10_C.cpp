#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> matrix;
vector<vector<int>> tree;
int n;
int m;

int getParent(int x) {
    return x - (x & -x);
}

int getNext(int x) {
    return x + (x & -x);
}

void sett(int row, int col, int val) {
    if (n == 0 || m == 0) return;

    for (int i = row + 1; i <= n; i = getNext(i))
        for (int j = col + 1; j <= m; j = getNext(j))
            tree[i][j] += val;
}

int sum(int row, int col) {
    int sum = 0;
    if (n == 0 || m == 0) return sum;

    for (int i = row; i > 0; i = getParent(i))
        for (int j = col; j > 0; j = getParent(j))
            sum += tree[i][j];

    return sum;
}

void update(int row, int col, int val) {
    if (n == 0 || m == 0) return;
    int delta = val - matrix[row][col];
    matrix[row][col] = val;
    sett(row, col, delta);
}

int sumRegion(int row1, int row2, int col1, int col2) {
    return sum(row2 + 1, col2 + 1) + sum(row1, col1) - sum(row1, col2 + 1) - sum(row2 + 1, col1);
}

int main() {
    cin >> n >> m;

    int b, g, w, y;
    cin >> b >> g >> w >> y;

    for (int i = 0; i < n; i++) {
        vector<int> map_row(m);
        for (int j = 0; j < m; j++) {
            char a;
            cin >> a;
            if (a == 'w')
                map_row[j] = b;
            else if (a == 'f')
                map_row[j] = g;
            else if (a == 'i')
                map_row[j] = w;
            else if (a == 'd')
                map_row[j] = y;
        }
        matrix.push_back(map_row);

        vector<int> tree_row(m + 1);
        tree.push_back(tree_row);
    }

    vector<int> tree_row(m + 1);
    tree.push_back(tree_row);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            sett(i, j, matrix[i][j]);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        char sym;
        cin >> sym;
        
        if (sym == 'R') {
            int r1, r2, c1, c2;
            cin >> r1 >> r2 >> c1 >> c2;
            cout << sumRegion(r1, r2, c1, c2) << endl;
        } else {
            int r, c;
            char t;
            cin >> r >> c >> t;
            int val = 0;

            if (t == 'w')
                val = b;
            else if (t == 'f')
                val = g;
            else if (t == 'i')
                val = w;
            else
                val = y;

            update(r, c, val);
        }
    }
}