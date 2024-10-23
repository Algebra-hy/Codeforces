#include <cstdio>
#include <algorithm>
using namespace std;
const int S=2000005;
const long long inf=(1ll<<60)-1;
int n,m;
long long a[S],dpL[S],dpR[S];
inline int getid(int i, int j) {
    if (i<0 || i>n || j>m || j<0) return 0;
    return (i-1)*(m+1)+j+1;
}
int main() {
    int T;scanf("%d",&T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j)
                scanf("%lld", a + getid(i, j));
            a[getid(i, 0)] = 0;
        }
        long long premax, pre, fmax;
        premax = -inf;
        pre = 0;
        for (int i = 0; i <= m; ++i) {
            pre += a[getid(1, i)];
            if (i == 0) dpR[getid(1, 0)] = -inf;
            else dpR[getid(1, i)] = pre + premax;
            premax = max(premax, -pre);
        }
        premax = -inf;
        pre = 0;
        for (int i = m; i >= 0; --i) {
            if (i == m) dpL[getid(1, i)] = -inf;
            else {
                pre += a[getid(1, i + 1)];
                dpL[getid(1, i)] = pre + premax;
            }
            premax = max(premax, -pre);
        }
        for (int i = 2; i <= n; ++i) {
            premax = -inf, pre = 0, fmax = -inf;
            dpR[getid(i, 0)] = -inf;
            for (int j = 1; j <= m; ++j) {//dpR
                pre += a[getid(i, j)];
                fmax = max(fmax, premax + max(dpL[getid(i - 1, j - 1)], dpR[getid(i - 1, j - 1)]));
                dpR[getid(i, j)] = fmax + pre;
                premax = max(premax, - pre + a[getid(i, j)]);
            }
            dpL[getid(i, m)] = -inf;
            premax = -inf;
            pre = 0;
            fmax = -inf;
            for (int j = m - 1; j >= 0; --j) {
                pre += a[getid(i, j + 1)];
                fmax = max(fmax, premax + max(dpL[getid(i - 1, j + 1)], dpR[getid(i - 1, j + 1)]));
                dpL[getid(i, j)] = fmax + pre;
                premax = max(premax, - pre + a[getid(i, j + 1)]);
            }
        }
//        for (int i=1;i<=n;++i) {
//            for (int j=0;j<=m;++j)
//                printf("%lld ",dpL[getid(i,j)]);
//            puts("");
//        }
        long long res=-inf;
        for (int i=0;i<=m;++i) {
            if (i>0) res=max(res,dpR[getid(n,i)]);
            if (i<m) res=max(res,dpL[getid(n,i)]);
        }
        printf("%lld\n",res);
    }
    return 0;
}