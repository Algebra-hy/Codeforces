#include <cstdio>
#include "vector"
#include <map>
#include <utility>
#include "set"
using namespace std;
const int S=2004;
int n,a[S],s[S];
map<int,pair<pair<int,int>, int>> mp;
int main() {
    int T;scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        for (int i=1;i<=n;++i)
            scanf("%d",a+i),s[i]=s[i-1]+a[i];
        pair<pair<int,int>,int> tmp;
        long long res=0;
        for (int l=0;l<=n;++l)
            for (int i=0,j,cnt,id,lal,lar;i+l<=n;++i) {
                j = i+l;
                id = s[i]+s[j];
                tmp = mp[id];
                cnt =  tmp.second;
                lal = tmp.first.first;
                lar = tmp.first.second;
                if (!lar) {
                    if (j<=i) cnt=0;
                    else cnt+=j-i-1;
                } else {
                    cnt += lal - i + j - lar - 2;
                }
                res += cnt;
                mp[id]= make_pair(make_pair(i,j), cnt);
            }
        for (int i=0;i<=n;++i)
            for (int j=i;j<=n;++j)
                mp[s[i]+s[j]]= make_pair(make_pair(0,0),0);
        printf("%lld\n",res);
    }
    return 0;
}