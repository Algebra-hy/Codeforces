//
// Created by Yang Hang on 2024/10/15.
//
#include <cstdio>
#include <algorithm>
using namespace std;
const int S=200005,D = 100001;
int n,h[S],nx[S],v[S],eg=1,a[S],b[S],fa[S];
inline void egadd(int uu,int vv) {
    nx[++eg]=h[uu];h[uu]=eg;
    v[eg]=vv;
}
long long f[S];
const int M = S*50;
const long long inf = 1ll<<60;
int sg[M],tot=0,lc[M],rc[M],root[M];

int cmp(long long x, long long y) {  // 因为用到了浮点数，所以会有精度误差
    if (x - y > 0) return -1;
    if (y - x > 0) return 1;
    return 0;
}

long long calc(int id,int x) {
    if (!id) return inf;
    return b[id]*1ll*(x-D) + f[id];
}

void upd(int &rt, int cl, int cr, int u) {  // 对线段完全覆盖到的区间进行修改
    int mid = (cl + cr) >> 1;
    if (!rt) {
        rt = ++tot;
        sg[rt] = u;
        return;
    }
    int &v = sg[rt];
    int bmid = cmp(calc(u, mid), calc(v, mid));
    if (calc(v, mid) > calc(u, mid))  // 在此题中记得判线段编号
        swap(u, v);
    if (calc(v, cl) <= calc(u,cl) && calc(v, cr) <= calc(u, cr))
        return;
    if (calc(v,cl) > calc(u,cl)) upd(lc[rt], cl, mid, u);
    else upd(rc[rt], mid+1, cr, u);
    // 上面两个 if 的条件最多只有一个成立，这保证了李超树的时间复杂度
}
long long query(int &rt, int l, int r, int d) {  // 查询
    if (!rt) return inf;
    int mid = (l + r) >> 1;
    long long res = calc(sg[rt], d);
    if (l == r) return res;
    return min(res, d<=mid?query(lc[rt], l, mid, d):query(rc[rt], mid + 1, r, d));
}
int merge(int x,int y, int l,int r) {
    if (!x || !y) return x|y;
    if (sg[y]) upd(x, l, r, sg[y]);
    int mid=(l+r)>>1;
    lc[x] = merge(lc[x], lc[y], l,mid);
    rc[x] = merge(rc[x], rc[y], mid+1,r);
    return x;
}
void dfs(int x) {
    for (int i=h[x];i;i=nx[i])
        if (v[i]!=fa[x]) {
            fa[v[i]]=x;
            dfs(v[i]);
            root[x] = merge(root[x], root[v[i]], 1, S);
        }
    f[x] = query(root[x], 1, S, a[x] + D);
    if (f[x] == inf) f[x] = 0;
    upd(root[x], 1, S, x);
}
int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
        scanf("%d",a+i);
    for (int i=1;i<=n;++i)
        scanf("%d",b+i);
    for (int i=1,uu,vv;i<n;++i) {
        scanf("%d%d",&uu,&vv);
        egadd(uu,vv);
        egadd(vv,uu);
    }
    dfs(1);
    for (int i=1;i<=n;++i) printf("%lld ", f[i]);
    return 0;
}