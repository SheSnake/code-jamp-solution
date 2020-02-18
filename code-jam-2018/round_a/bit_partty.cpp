#include <iostream>
#include <string.h>
#include <algorithm>

// binary search every T to check if T satisfy

using namespace std;
#define N 1000;
int compare(const void* a, const void* b)
{
    return (*(std::int64_t*)b) - (*(std::int64_t*)a);
}

int main()
{
    int T;
    cin >> T;
    std::int64_t M[1000];
    std::int64_t S[1000];
    std::int64_t P[1000];
    for (int t = 1; t <= T; ++t)
    {
        std::int64_t R, B, C;
        cin >> R >> B >> C;
        std::int64_t max_used = 0;
        for (int c = 0; c < C; ++c)
        {
            cin >> M[c] >> S[c] >> P[c];
            std::int64_t used = B * S[c] + P[c];
            if (used > max_used)
            {
                max_used = used;
            }
        }
        std::int64_t lo = 0, hi = max_used + 1;
        std::int64_t can_finished[1000];
        while (hi > lo)
        {
            memset(can_finished, 0, 1000 * sizeof(std::int64_t));
            std::int64_t mi = (hi + lo) >> 1;
            //cout << "mi:"<< mi << " " << "hi:"<< hi << " lo: "<< lo <<endl;
            for (int c = 0; c < C; ++c)
            {
                std::int64_t count = (mi - P[c]) / S[c];
                if (count < 0) count = 0;
                if (count > M[c]) count = M[c];
                can_finished[c] = count;
            }
            qsort(can_finished, 1000, sizeof(std::int64_t), compare);
            std::int64_t count = 0;
            for (int i = 0 ; i < R; ++i)
            {
                count += can_finished[i];
            }
            if (count >= B)
            {
                hi = mi;
            }
            else if (count < B)
            {
                lo = mi + 1;
            }
        }
        printf("Case #%d: %ld\n", t, lo);
    }
}
