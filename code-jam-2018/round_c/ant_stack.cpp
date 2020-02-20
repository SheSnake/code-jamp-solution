#include <iostream>
#include <string.h>
using namespace std;

int64_t dp[100000][200];
int64_t w[100000];
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        memset(dp, -1, 100000 * 200 * sizeof(int64_t));
        memset(w, 0, 100000 * sizeof(int64_t));
        int N;
        cin >> N;
        for (int i = 0; i < N; ++i)
        {
            cin >> w[i];
        }
        dp[0][0] = 0;
        dp[0][1] = w[0];
        for (int i = 1; i < N; ++i)
        {
            dp[i][0] = 0;
            for (int j = 1; j < 200; ++j)
            {
                if (j > i + 1) break;
                if (dp[i - 1][j - 1] != -1)
                {
                    if (w[i] * 6 >= dp[i - 1][j - 1])
                    {
                        int64_t cur = dp[i - 1][j - 1] + w[i];
                        if (dp[i - 1][j] == -1)
                        {
                            dp[i][j] = cur;
                        }
                        else if (cur < dp[i - 1][j])
                        {
                            dp[i][j] = cur;
                        }
                        else
                        {
                            dp[i][j] = dp[i - 1][j];
                        }
                    }
                    else
                    {
                        dp[i][j] = dp[i - 1][j];
                    }
                }
                else
                {
                    dp[i][j] = -1;
                }
            }
        }
        int i = 1;
        for (; i < 200; ++i)
        {
            if (dp[N - 1][i] == -1) break;
        }
        printf("Case #%d: %d\n", t, i - 1);
    }
}
