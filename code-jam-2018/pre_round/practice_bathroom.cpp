#include <iostream>
using namespace std;


int main()
{
    int64_t T;
    cin >> T;
    for (int64_t t = 0; t < T; ++t)
    {
        int64_t N, K;
        cin >> N >> K;
        int64_t odds = 0, evens = 0;
        if (N & 1 == 1) 
        {
            if (((N - 1) / 2) & 1 == 1)
            {
                odds = 2;
            }
            else
            {
                evens = 2;
            }
        }
        else
        {
            odds = 1;
            evens = 1;
        }
        int64_t l = 2;
        K -= 1;
        int64_t max = N / 2;
        int64_t min = (N - 1) / 2;
        while (K > l)
        {
            K -= l;
            if (max & 1 == 1)
            {
                int64_t n_evens = 0;
                if (((max - 1) / 2) & 1 == 1)
                {
                    odds = odds * 2 + evens;
                }
                else
                {
                    n_evens = odds * 2;
                    odds = evens;
                }
                evens += n_evens;
            }
            else
            {
                int64_t n_evens = 0;
                if ((((max - 2) / 2) & 1) == 1)
                {
                    odds = odds * 2 + evens;
                }
                else
                {
                    n_evens = odds * 2;
                    odds = evens;
                }
                evens += n_evens;
            }
            min = (min - 1) / 2;
            max = max / 2;
            l *= 2;
        }
        int64_t res_a = max;
        int64_t res_b = min;
        if (K > 0)
        {
            if (max & 1 == 1)
            {
                if (odds >= K)
                {
                    res_b = res_a = (max - 1) / 2;
                }
                else
                {
                    res_a = min / 2;
                    res_b = (min - 1) / 2;
                }
            }
            else
            {
                if (evens >= K)
                {
                    res_a = max / 2;
                    res_b = (max - 1) / 2;
                }
                else
                {
                    res_b = res_a = (min - 1) / 2;
                }
            }
        }

        printf("Case #%ld: %lld %lld\n", t + 1, res_a, res_b);
    }
    return 0;
}
