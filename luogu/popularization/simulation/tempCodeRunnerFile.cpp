#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1e5 + 10;
int n, m, ans = 1;
struct p{
    char s[10];
    int c;
}a[maxn];
int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    cin >> a[i].c >> a[i].s;
    for(int i = 1; i <= n; ++i)
    a[i].c = (a[i].c) ? -1 : 1;
    
    int tmp, s;
    p peo = a[1];
    for(int i = 1; i <= m; ++i){
        cin >> tmp >> s;
        if(tmp){
            ans += peo.c * s;
        }
        else{
            ans += -peo.c * s;
        }

        if(ans < 0)
            ans = n - (-ans) % n;
        else
            ans = ans % n;
        if(ans == 0) ans = n;
        peo = a[ans];
        cout << ans << '\t' << peo.s  << endl;
        
    }
    cout << peo.s << endl;
}