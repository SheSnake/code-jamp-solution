#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

// view analysis: try each interval and for each new interval cut off the invalid

struct Interval
{
    double l;
    double r;
    Interval(double l = 0, double r = 0): l(l), r(r) {}
};

int compare(const void* a, const void* b)
{
    return ((Interval*)a)->l - ((Interval*)b)->l;
}

vector<Interval> merge(vector<Interval>& s)
{
    if (s.size() == 0) return s;
    vector<Interval> res;
    Interval cur = s[0];
    for (int i = 1; i < s.size(); ++i)
    {
        if (s[i].l <= cur.r)
        {
            if (s[i].r > cur.r)
            {
                cur.r = s[i].r;
            }
        }
        else
        {
            res.push_back(cur);
            cur = s[i];
        }
    }
    res.push_back(cur);
    return res;
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        int N; double P;
        cin >> N >> P;
        Interval LR[100];
        double cur_P = 0.0;
        for (int i = 0; i < N; ++i)
        {
            int H, W;
            cin >> H >> W;
            double l = H > W ? W : H;
            double r = sqrt(H * H + W * W);
            LR[i].l = l * 2;
            LR[i].r = r * 2;
            cur_P += (H + W) * 2;
        }

        vector<Interval> s;
        s.push_back(Interval(0, 0));
        double most_add_P = P - cur_P;
        for (int i = 0; i < N; ++i)
        {
            int size = s.size();
            for (int j = 0; j < size; ++j)
            {
                if (s[j].l + LR[i].l > most_add_P) continue;
                s.push_back(Interval(s[j].l + LR[i].l, s[j].r + LR[i].r));
            }
            qsort(s.data(), s.size(), sizeof(Interval), compare);
            //for (int j = 0; j < s.size(); ++j)
            //{
            //    cout << "after sort inter: "<<s[j].l << " "<< s[j].r << endl;
            //}
            s = merge(s);
            //for (int j = 0; j < s.size(); ++j)
            //{
            //    cout << "inter: "<<s[j].l << " "<< s[j].r << endl;
            //}
        }
        double res = cur_P;
        if (s.size() > 0)
        {
            if (s[s.size() - 1].r + res >= P)
            {
                printf("Case #%d: %.6f\n", t, P);
            }
            else
            {
                res += s[s.size() - 1].r;
                printf("Case #%d: %.6f\n", t, res);
            }
        }
    }
}
