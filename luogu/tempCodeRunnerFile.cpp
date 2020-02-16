#include<bits/stdc++.h>
using namespace std;
const int maxn = 51, maxm = 1e6 + 10;
long long T,n, dp[maxn][maxm];//前i件食材，时间j下 的最大美味指数
struct node{
    long long a, b, c;
}d[maxn];
bool cmp(node x, node y){
    return x.b * y.c > y.b * x.c;
}
int main()
{
    cin >> T >> n;
    for(int i = 1; i <= n; ++i)
        cin >> d[i].a;
    for(int i = 1; i <= n; ++i)
        cin >> d[i].b;
    for(int i = 1; i <= n; ++i)
        cin >> d[i].c;
    sort(d + 1, d + 1 + n, cmp);
    for(int i = 1; i <= n; ++i)
        for(long long j = 0; j <= T; ++j)
            if(j >= d[i].c)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - d[i].c] + d[i].a - j * d[i].b);
    long long ans = 0;
    for(int i = 0; i <= T; ++i)
        ans = max(ans, dp[n][i]);
    cout << ans << endl;
    //cout << ans << endl;
}