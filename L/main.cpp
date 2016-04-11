#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
using namespace std;

void add(int i, int delta, vector<int> &ftree, int n)
{
        for (i ; i < n; i |= i + 1)
                ftree[i] += delta;
}

void get(int l, int r, int& res, vector<int> &ftree)
{
        for (r ; r >= 0; r = (r & (r + 1)) - 1)
                res += ftree[r];

        for (l ; l >= 0; l = (l & (l + 1)) - 1)
                res -= ftree[l];
}

int main()
{

    freopen("permutation.in", "rt", stdin);
    freopen("permutation.out", "wt", stdout);
    ios_base::sync_with_stdio(false);

    int n, m, x, y, k, l, res;
    vector<long long> a;
    vector<int> ftree;
    scanf("%d %d", &n, &m);

    a.resize(n);
    ftree.assign(n, 0);

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
    }

    while (m--)
    {
        res = 0;
        scanf("%d %d", &x, &y);
        scanf("%d %d", &k, &l);
        for (int i = x; i <= y; ++i) {
            if (a[i] > k && a[i] < l)
                    add(i, 1, ftree, n);
        }
        get(x - 1, y, res, ftree);
        printf("%d\n", res);
    }

    return 0;
}
