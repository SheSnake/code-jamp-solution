#include <algorithm>
#include <iostream>

using namespace std;

struct Int
{
    int v;
    bool odd;
};

int compare(const void* a, const void* b)
{
    return ((Int*)a)->v - ((Int*) b)->v;
}

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int N;
        cin >> N;
        Int v[N];
        Int v_b[N];
        int a = 0, b = 0;
        for (int i = 0; i < N; ++i)
        {
            if ((i & 1) == 0)
            {
                cin >> v[a].v;
                a ++;
            }
            else
            {
                cin >> v_b[b].v;
                b ++;
            }
        }
        bool ok = true;
        qsort(v, a, sizeof(Int), compare);
        qsort(v_b, b, sizeof(Int), compare);
        int a_i = 0;
        int b_i = 0;
        while (a_i < a && b_i < b)
        {
            if (v[a_i].v > v_b[b_i].v)
            {
                ok = false;
                printf("Case #%d: %d\n", t + 1, a_i * 2);
                break;
            }
            if (a_i + 1 != a && v_b[b_i].v > v[a_i + 1].v)
            {
                ok = false;
                printf("Case #%d: %d\n", t + 1, b_i * 2 + 1);
                break;
            }
            a_i ++;
            b_i ++;
        }

        if (ok)
        {
            printf("Case #%d: OK\n", t + 1);
        }

    }
}
