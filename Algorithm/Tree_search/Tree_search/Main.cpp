#include <iostream>
#include <vector>
#include <limits>
#include <windows.h>
#include<locale.h>

using namespace std;

// Функція для друку дерева
void printTree(const vector<vector<int>>& root, int i, int j, const string& indent) {
    if (i > j) {
        cout << indent << "d" << j << endl; // d - фальшивий ключ
        return;
    }
    int r = root[i][j];
    cout << indent << "k" << r << endl;
    printTree(root, i, r - 1, indent + "  ");
    printTree(root, r + 1, j, indent + "  ");
}

// Побудова оптимального дерева
void optimalBST(const vector<double>& p, const vector<double>& q, int n) {
    vector<vector<double>> e(n + 2, vector<double>(n + 1));
    vector<vector<double>> w(n + 2, vector<double>(n + 1));
    vector<vector<int>> root(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = numeric_limits<double>::infinity();
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "Минимальна очикувана вартисть пошуку: " << e[1][n] << endl;
    cout << "\nСтруктура дерева:\n";
    printTree(root, 1, n, "");
}

int main() {
    setlocale(LC_CTYPE, "ukr");

    int n = 4;
    vector<double> p = { 0, 0.15, 0.10, 0.05, 0.10 }; // 1-based індексація
    vector<double> q = { 0.05, 0.10, 0.05, 0.05, 0.10 };

    optimalBST(p, q, n);
    return 0;
}

