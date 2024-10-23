#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int S=3003,inf=(1<<30)-1;
int n,tr[1<<5][S],m,t[S];
struct node {
    int a,b,c;
}a[S];
void tradd(int tr[], int x, int o) {
    for (int i=x;i<=n;i+=i&-i)
        tr[i]=max(tr[i],o);
}
int trcal(int tr[], int x) {
    int ret=-inf;
    for (int i=x;i;i-=i&-i)
        ret=max(ret,tr[i]);
    return ret;
}
inline bool cmp(const node &a,const node &b) {
    return a.a<b.a;
}
inline void init(int tr[]) {
    for (int i=1;i<=n;++i)
        tr[i]=-inf;
}
int main () {
    srand(2333);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
        scanf("%d",&a[i].a);
    for (int i=1;i<=n;++i)
        scanf("%d",&a[i].b);
    for (int i=1;i<=n;++i)
        scanf("%d",&a[i].c);
    //sort(a+1,a+1+n,cmp);
    int lim = 1<<m;
    int T = 300;
    int res = -inf;
    while (T--) {
        for (int i=1;i<=n;++i)
            t[i]=rand()%m;
        for (int j = 0; j < lim; ++j)
            init(tr[j]);
        tradd(tr[0], 1, 0);
        for (int i = 1; i <= n; ++i) {
            int cl = t[a[i].b];
            for (int j = 0; j < lim; ++j) {
                //printf("%d %d\n",i,j);
                if (!((j>>cl)&1))
                    tradd(tr[j|(1<<cl)], a[i].a, trcal(tr[j],a[i].a) + a[i].c);
            }
        }
        res=max(res,trcal(tr[lim-1], n));
    }
    if (res<0) puts("-1");
    else printf("%d\n",res);
    return 0;
}