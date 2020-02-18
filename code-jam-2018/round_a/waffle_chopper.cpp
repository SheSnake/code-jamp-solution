#include <iostream>
#include <string.h>
#include <memory>
using namespace std;

// solution: find cut point and check if each waffle is valid

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++ t)
    {
        int mark[101][101];
        int h_pos[100];
        int v_pos[100];
        memset(mark, 0, 101 * 101 * 4);
        memset(h_pos, 0, 100 * 4);
        memset(v_pos, 0, 100 * 4);
        int total = 0;
        int R, C, H, V;
        cin >> R >> C >> H >> V;
        for (int i = 0; i < R; ++i)
        {
            std::string line;
            cin >> line;
            for (int j = 0; j < C; ++j)
            {
                if (line[j] == '@')
                {
                    mark[i][j] = 1;
                    total ++;
                }
            }
        }
        if (total % (H + 1) != 0 || total % (V + 1) != 0 || total % ((V + 1) * (H + 1)) != 0)
        {
            printf("Case #%d: IMPOSSIBLE\n", t);
            continue;
        }

        int h_num = total / (H + 1);
        int v_num = total / (V + 1);
        int per_num = total / ( (H + 1) * (V + 1) );

        bool success = true;
        int s = 0;
        for (int i = 0; i < H; ++i)
        {
            int found = 0;
            for (int j = s; j < R - 1; ++j)
            {
                // cut between waffle[j] and waffle[j + 1]
                for (int k = 0; k < C; ++k)
                {
                    found += mark[j][k];
                }
                if (found == h_num) {
                    h_pos[i] = j;
                    s = j + 1;
                    break;
                }
                if (found > h_num)
                {
                    success = false;
                    break;
                }
            }
            if (found < h_num)
            {
                success = false;
                break;
            }
        }
        if (!success)
        {
            printf("Case #%d: IMPOSSIBLE\n", t);
            continue;
        }

        s = 0;
        for (int i = 0; i < V; ++i)
        {
            int found = 0;
            for (int j = s; j < C - 1; ++j)
            {
                // cut between waffle[col[j]] and waffle[col[j + 1]]
                for (int k = 0; k < R; ++k)
                {
                    found += mark[k][j];
                }
                if (found == v_num)
                {
                    v_pos[i] = j;
                    s = j + 1;
                    break;
                }
                if (found > v_num)
                {
                    success = false;
                    break;
                }
            }
            if (found < v_num)
            {
                success = false;
                break;
            }
        }
        if (!success)
        {
            printf("Case #%d: IMPOSSIBLE\n", t);
            continue;
        }

        for (int i = 0; i < H + 1; ++i)
        {
            int begin_h = i == 0 ? 0 : h_pos[i - 1] + 1;
            int end_h = i == H ? R - 1 : h_pos[i];
            for (int j = 0; j < V + 1; ++j)
            {
                int begin_v = j == 0 ? 0 : v_pos[j - 1] + 1;
                int end_v = j == V ? C - 1 : v_pos[j];
                int num = 0;
                for (int r = begin_h; r <= end_h; ++r)
                {
                    for (int c = begin_v; c <= end_v; ++c)
                    {
                        num += mark[r][c];
                    }
                }
                if (num != per_num)
                {
                    success = false;
                    break;
                }
            }
            if (!success)
            {
                break;
            }
        }
        if (!success)
        {
            printf("Case #%d: IMPOSSIBLE\n", t);
        }
        else
        {
            printf("Case #%d: POSSIBLE\n", t);
        }
    }
}
