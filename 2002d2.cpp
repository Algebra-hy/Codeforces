#include <cstdio>
#include <cstdlib>
#include <set>
using namespace std;
const int S=300003;
int n,q,fa[S],h[S],nx[S],v[S],sz[S],eg,p[S],r[S],in[S],dfn[S],_=0;
inline void egadd(int uu,int vv) {
    nx[++eg]=h[uu];h[uu]=eg;
    v[eg]=vv;
}
void dfs(int x) {
    sz[x]=1;dfn[x]=++_;
    for (int i=h[x];i;i=nx[i]) {
        dfs(v[i]);
        sz[x] += sz[v[i]];
    }
}
set<int> st[S];
set<int>::iterator it;
multiset<int>::reverse_iterator jt;
bool pd(int i) {
    if (st[i].size()!=in[i])
        return false;
    if (st[i].empty())
        return true;
    it=st[i].begin();
    jt=st[i].rbegin();
    bool ret=(r[i]+1==*it && *jt+sz[p[*jt]]<=r[i]+sz[i]);
    return ret;
}
inline bool pd2(int i) {
    if (r[i]==1) {
        return i==1;
    }
    if (i==1) return false;
    if (p[r[i]-1]==fa[i]) return true;
    if (sz[p[r[i]-1]]!=1) return false;
    if (!(dfn[fa[i]]<=dfn[p[r[i]-1]] && dfn[p[r[i]-1]]<=dfn[fa[i]]+sz[fa[i]]-1))
        return false;
    return true;
}
set<int> pr,qr;
int main() {
    srand(2333);
    int T;scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&q);
        for (int i=1;i<=n;++i)
            h[i]=in[i]=0;
        eg=1;_=0;
        for (int i=2;i<=n;++i) {
            scanf("%d", fa + i);
            egadd(fa[i],i);
            ++in[fa[i]];
        }
        dfs(1);
        for (int i=1;i<=n;++i)
            scanf("%d",p+i),r[p[i]]=i;
        int su=0;//puts("c");
        int sum=0;
        for (int i=1;i<=n;++i) {
            st[i].clear();
            for (int j=h[i];j;j=nx[j]) {
                st[i].insert(r[v[j]]);
            }
            if (pd(i))
                ++su;
            if (pd2(i)) ++sum;
        }
        // printf("%d\n",su);
        int x,y;
        while (q--) {
            scanf("%d%d",&x,&y);
            pr.clear();qr.clear();
            pr.insert(p[x]);qr.insert(p[x]);
            pr.insert(p[y]);qr.insert(p[y]);
            if (fa[p[x]]) pr.insert(fa[p[x]]);
            if (fa[p[y]]) pr.insert(fa[p[y]]);
            if (x+1<=n) qr.insert(p[x+1]);
            if (y+1<=n) qr.insert(p[y+1]);
            for (int o: pr) {
                if (pd(o)) --su;
            }
            for (int o: qr) {
                if (pd2(o)) --sum;
            }
            if (fa[p[x]]) st[fa[p[x]]].erase(x);//,st2[fa[p[x]]].erase(x+sz[p[x]]-1);
            if (fa[p[y]]) st[fa[p[y]]].erase(y);//,st2[fa[p[y]]].erase(y+sz[p[y]]-1);
            //printf("midsu = %d\n",su);
            swap(r[p[x]],r[p[y]]);
            swap(p[x],p[y]);
            if (fa[p[x]]) st[fa[p[x]]].insert(x);//,st2[fa[p[x]]].insert(x+sz[p[x]]-1);
            if (fa[p[y]]) st[fa[p[y]]].insert(y);//,st2[fa[p[y]]].insert(y+sz[p[y]]-1);
            for (int o: pr) {
                if (pd(o)) ++su;
            }
            for (int o: qr) {
                if (pd2(o)) ++sum;
            }
            //printf("endsu = %d\n",su);
            puts(su==n && p[1]==1 && sum==n?"YES":"NO");
        }
    }
    return 0;
}