#include <iostream>
using namespace std;


int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int D, N;
        cin >> D >> N;
        double max_t = 0;
        for (int i = 0; i < N; ++i)
        {
            int K, S;
            cin >> K >> S;
            double t = double(D - K) / double(S);
            max_t = max_t > t ? max_t : t;
        }
        double s = double(D) / max_t;
        printf("Case #%d: %.7f \n", t + 1, max_s);
    }
    return 0;
}
