#include <cstdio>
#include <algorithm>
#include "vector"
using namespace std;
const int S=2000003;
int tr[S][26],fail[S],len[S],last=0,tot=0,e[S];
char c[S];
int n,h[S],nx[S],v[S],eg=1;
long long res=0;
void insert(int &last,int c)
{
    c-='a';
    int p=last,now=++tot;e[tot]=1;
    len[now]=len[p]+1;
    while (p!=-1 && !tr[p][c])
    {
        tr[p][c]=now;
        p=fail[p];
    }
    if (p==-1) fail[now]=0;
    else
    {
        int q=tr[p][c];
        if (len[p]+1==len[q])
            fail[now]=q;
        else
        {
            int w=++tot;
            len[w]=len[p]+1;
            fail[w]=fail[q];
            for (int i=0;i<26;++i)
                tr[w][i]=tr[q][i];
            fail[q]=fail[now]=w;
            while (p!=-1 && tr[p][c]==q)
            {
                tr[p][c]=w;
                p=fail[p];
            }
        }
    }
    last=now;
}
inline void egadd(int uu,int vv)
{
    nx[++eg]=h[uu];h[uu]=eg;
    v[eg]=vv;
}
const int N = 1000005;
vector<int> factor[N];
void dfs(int x)
{
    for (int i=h[x];i;i=nx[i])
    {
        dfs(v[i]);
        e[x]+=e[v[i]];
    }
    auto o1 = upper_bound(factor[e[x]].begin(), factor[e[x]].end(), len[x])-1;
    auto o2 = lower_bound(factor[e[x]].begin(), factor[e[x]].end(), len[fail[x]]+1);
    //printf("%d %d\n",e[x],(o1-o2+1 - (o1 == factor[e[x]].end())));
    if (x) res+=e[x]*(o1-o2+1 - (o1 == factor[e[x]].end()));
}
int main()
{
    fail[0]=-1;
    scanf("%d%s",&n,c+1);
    for (int i=1;i<N;++i)
        for (int j=i;j<N;j+=i)
            factor[j].push_back(i);
    //puts("c");
    for (int i=1;i<=n;++i)
        insert(last,c[i]);
    for (int i=1;i<=tot;++i)
        egadd(fail[i],i);
    dfs(0);
    printf("%lld\n",res);
    return 0;
}