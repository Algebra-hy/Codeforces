#include <cstdio>
#include "algorithm"
using namespace std;
const int S=5005,inf=(1<<30)-1;
int n,m,a[S],f[S][S],s0[S],s1[S],nxt[S],pre[S];
struct node {
    int l,r;
}b[S];
inline bool cmp(const node &a,const node &b) {
    if (a.l==b.l) return a.r<b.r;
    return a.l<b.l;
}
int cl[S],nx[S];
int tot;
int main() {
    int T;scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;++i) cl[i]=-1,nx[i]=0;
        for (int i=1;i<=m;++i)
            scanf("%d%d",&b[i].l,&b[i].r);
        sort(b+1,b+1+m,cmp);
        bool flag = false;
        for (int i=1,j;i<m && !flag;++i) {
            j=i+1;
            if (b[i].r>=b[j].l) {
                for (int k = b[i].l; k < b[j].l && !flag; ++k)
                    if (cl[k] == 1) flag = true;
                    else cl[k] = 0;
                for (int k = min(b[i].r + 1, b[j].r + 1); !flag && (k <= b[j].r || k <= b[i].r); ++k)
                    if (cl[k] == 0) flag = true;
                    else cl[k] = 1;
            }
        }
        for (int i=1;i<=n;++i) {
            s0[i]=s0[i-1]+(cl[i]!=1);
            s1[i]=s1[i-1]+(cl[i]!=0);
        }
        nxt[n+1]=n+1;
        for (int i=n;i;--i)
            if (cl[i]==-1) nxt[i]=i;
            else nxt[i]=nxt[i+1];
        pre[0]=0;
        for (int i=1;i<=n;++i)
            if (cl[i]==-1) pre[i]=i;
            else pre[i]=pre[i-1];
        //for (int i=1;i<=n;++i) printf("%d ",cl[i]);puts("cl");
        for (int i=1;i<=m && !flag;++i) {
            if (!(s1[b[i].r]-s1[b[i].l-1] && s0[b[i].r]-s0[b[i].l-1])) flag = true;
        }
        if (flag) {
            puts("-1");
            continue;
        }
        tot=0;
        for (int i=1;i<=m;++i) {
            b[i].l=nxt[b[i].l];
            b[i].r=pre[b[i].r];
            if (b[i].l<=b[i].r && (!tot || b[i].l>b[tot].r))
                b[++tot]=b[i];
        }
        m=tot;
        //for (int i=1;i<=m;++i) printf("%d %d\n",b[i].l,b[i].r);puts("=== b ===");
        for (int i=1;i<=m;++i)
            nx[b[i].l]=b[i].r;
        for (int i=0;i<=n;++i)
            for (int j=0;j<=n;++j)
                f[i][j]=-inf;
        f[0][0]=0;
        for (int i=0;i<n;++i) {
            if (cl[i+1]==-1) {
                if (nx[i+1]) {
                    for (int j=0;j<=i;++j) {
                        for (int k=1;k<=nx[i+1]-(i+1) && j+k<=nx[i+1];++k) {
                            f[nx[i+1]][j+k]=max(f[nx[i+1]][j+k], f[i][j] + j*(nx[i+1]-i-k));
                        }
                    }
                    i = nx[i+1]-1;
                } else {
                    for (int j=0;j<=i;++j) {
                        f[i+1][j] = max(f[i+1][j],f[i][j]+j);
                        f[i+1][j+1] = max(f[i+1][j+1], f[i][j]);
                    }
                }
            } else if (cl[i+1]==0) {
                for (int j=0;j<=i;++j)
                    f[i+1][j]=max(f[i][j] + j,f[i+1][j]);
            } else if (cl[i+1]==1) {
                for (int j=0;j<=i;++j)
                    f[i+1][j+1]=max(f[i][j],f[i+1][j+1]);
            }
        }
        int res=-inf;
        for (int i=0;i<=n;++i)
            res=max(res,f[n][i] + i*(i-1)/2 + (n-i)*(n-i-1)/2);
        if (res<0) puts("-1");
        else printf("%d\n",res);
    }
}