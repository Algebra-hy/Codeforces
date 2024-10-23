#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100005;
int n,q,k,a[N],f[N],g[N];
struct node {
    int l,r,ans;
}b[N];
int main() {
    int T;scanf("%d",&T);
    while (T--) {
        scanf("%d%d%d",&n,&q,&k);
        for (int i=1;i<=n;++i)
            scanf("%d",a+i);
        for (int i=1;i<=q;++i)
            scanf("%d%d",&b[i].l,&b[i].r),b[i].ans=0;
        for (int i=1;i*i<=k;++i) {
            for (int j=1;j<=n;++j) {
                f[j]=f[j-1]+(a[j]<=i);
                g[j]=g[j-1]+(a[j]>=(k/(i+1) + 1));
            }
            for (int j=1;j<=q;++j) {
                int o = f[b[j].r]-f[b[j].l-1];
                int p = g[b[j].r]-g[b[j].l-1];
                if (min(o, n/2) < min(p, n/2)) {
                    b[i].ans = max(b[i].ans, (p-o+1)/2);
                }
            }
        }
        for (int i=1;i<=q;++i)
            printf("%d ",b[i].ans);
        puts("");
    }
    return 0;
}