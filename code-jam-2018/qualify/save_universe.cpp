#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int D;
        string P;
        cin >> D >> P;
        vector<int> c_num;
        int c = 0;
        for (int i = 0; i < P.size(); ++i)
        {
            char inst = P.at(i);
            if (inst == 'C')
            {
                c ++;
            }
            else if (inst == 'S')
            {
                c_num.push_back(c);
                c = 0;
            }
        }
        vector<int> c_total;
        int total = 0;
        int64_t cur_d = 0;
        for (int i = 0; i < c_num.size(); ++i)
        {
            total += c_num[i];
            c_total.push_back(total);
            cur_d += pow(2, total);
        }

        int res = 0;
        int ss_num = 1;
        for (int i = c_num.size() - 1; i >= 0; --i)
        {
            int c_to_swap = c_num[i];
            if (c_to_swap == 0)
            {
                ss_num ++;
                continue;
            }
            int max_can_reduce = pow(2, c_total[i]) - pow(2, c_total[i] - c_to_swap);
            if (cur_d - max_can_reduce * ss_num > D)
            {
                cur_d -= max_can_reduce * ss_num;
                res += ss_num * c_to_swap;
                c_num[i] = 0;
                for (int j = 0; j < ss_num; ++j)
                {
                    c_total[i + j] -= c_to_swap;
                }
                ss_num += 1;
                continue;
            }
            if (cur_d <= D)
            {
                break;
            }
            for (int j = 0; j < c_to_swap; ++j)
            {
                int reduce = pow(2, c_total[i]) - pow(2, c_total[i] - 1);
                for (int k = 0; k < ss_num; ++k)
                {
                    cur_d -= reduce;
                    c_total[i + k] -= 1;
                    res += 1;
                    if (cur_d <= D)
                    {
                        break;
                    }
                }
                if (cur_d <= D)
                {
                    break;
                }
            }
            break;
        }
        if (cur_d <= D)
        {
            printf("Case #%d: %d\n", t + 1, res);
        }
        else
        {
            printf("Case #%d: %s\n", t + 1, "IMPOSSIBLE");
        }
    }
}
