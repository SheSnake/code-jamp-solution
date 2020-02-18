#include <iostream>
#include <string.h>

using namespace std;


int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        int32_t D[100000], A[100000], B[100000];
        int32_t max[100000];
        memset(D, 0, 100000 * sizeof(int32_t));
        memset(A, 0, 100000 * sizeof(int32_t));
        memset(B, 0, 100000 * sizeof(int32_t));
        memset(max, 0, 100000 * sizeof(int32_t));
        int S;
        cin >> S;
        for (int s = 0; s < S; ++s)
        {
            cin >> D[s] >> A[s] >> B[s];
        }

        int32_t M = D[0] + A[0];
        int32_t N = D[0] - B[0];
        max[0] = 1;
        for (int i = 1; i < S; ++i)
        {
            int32_t cur_m = D[i] + A[i];
            int32_t cur_n = D[i] - B[i];
            if (cur_m == M || cur_n == N)
            {
                max[i] = max[i - 1] + 1;
            }
            else
            {
                bool m_can_change = true;
                bool n_can_change = true;

                int32_t M1 = cur_m, N1 = cur_n;
                int32_t M2 = cur_m, N2 = cur_n;
                int32_t num = 1;
                for (int p = i - 1; p >= 0; --p)
                {
                    int32_t p_m = D[p] + A[p];
                    int32_t p_n = D[p] - B[p];
                    if (p_m == M1)
                    {
                        num += 1;
                    }
                    else
                    {
                        if (n_can_change)
                        {
                            N1 = p_n;
                            n_can_change = false;
                        }

                        if (p_n == N1)
                        {
                            num += 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                int32_t num2 = 1;
                for (int p = i - 1; p >= 0; --p)
                {
                    int32_t p_m = D[p] + A[p];
                    int32_t p_n = D[p] - B[p];
                    if (p_n == N2)
                    {
                        num2 += 1;
                    }
                    else
                    {
                        if (m_can_change)
                        {
                            M2 = p_m;
                            m_can_change = false;
                        }

                        if (p_m == M2)
                        {
                            num2 += 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                if (num > num2)
                {
                    max[i] = num;
                    M = M1;
                    N = N1;
                }
                else {
                    max[i] = num2;
                    M = M2;
                    N = N2;
                }
            }
        }

        int32_t res = max[0];
        for (int i = 0; i < S; ++i)
        {
            if (max[i] > res)
            {
                res = max[i];
            }
        }

        int32_t res2 = 0;
        for (int i = 0; i < S; ++i)
        {
            if (max[i] == res)
            {
                res2 += 1;
            }
        }
        printf("Case #%d: %d %d\n", t, res, res2);
    }
}
