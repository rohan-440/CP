#include <bits/stdc++.h>
using namespace std;

class Sgt
{
public:
    vector<int> v;
    Sgt(int n)
    {
        v.resize(4 * n);
    }

    void build(vector<int> &arr, int ind, int l, int r)
    {
        if (l == r)
        {
            v[ind] = arr[l];
        }
        else
        {
            int mid = (l + r) / 2;
            build(arr, 2 * ind + 1, l, mid);
            build(arr, 2 * ind + 2, mid + 1, r);
            v[ind] = v[2 * ind + 1] + v[2 * ind + 2];
        }
    }

    int sum(int ind, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return v[ind];
        int tm = (tl + tr) / 2;
        return sum(2 * ind + 1, tl, tm, l, min(tm, r)) + sum(2 * ind + 2, tm + 1, r, max(tm + 1, l), r);
    }

    void update(int ind, int tl, int tr, int pos, int new_val)
    {
        if (tl == tr)
            v[ind] = new_val;
        else
        {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
            {
                update(2 * ind + 1, tl, tm, pos, new_val);
            }
            else
            {
                update(2 * ind + 2, tm + 1, tr, pos, new_val);
            }
            v[ind] = v[2 * ind + 1] + v[2 * ind + 2];
        }
    }

    void print()
    {
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << " ";
        }
    }
};