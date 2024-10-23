#include "bits/stdc++.h"
using namespace std;
const int S=4005,inf=(1<<30)-1;
int tr[S][12],tot=0,fail[S],h[S],v[S],nx[S],eg=1,st[S];
long long c[S];
void insert(char s[], int cc)
{
    int o=0;
    for (int i=0;s[i];i++)
    {
        int j=s[i]-'a';
        if (!tr[o][j])
            tr[o][j]=++tot;
        o=tr[o][j];
    }
    c[o]+=cc;
    //printf("%d %d\n",o,c[o]);
}
inline void egadd(int uu,int vv)
{
    nx[++eg]=h[uu];h[uu]=eg;
    v[eg]=vv;
}
queue<int> q;
void build()
{
    memset(fail,0,sizeof(fail));
    for (int i=0;i<12;i++)
        if (tr[0][i])
        {
            q.push(tr[0][i]);
            egadd(0,tr[0][i]);
        }
    while (!q.empty())
    {
        int x=q.front();q.pop();
        for (int i=0;i<12;i++)
            if (tr[x][i])
            {
                fail[tr[x][i]]=tr[fail[x]][i];
                q.push(tr[x][i]);
                egadd(fail[tr[x][i]],tr[x][i]);
            }
            else tr[x][i]=tr[fail[x]][i];
    }
}
void dfs(int x) {
    for (int i=h[x];i;i=nx[i]) {
        c[v[i]]+=c[x];
        dfs(v[i]);
    }
}
int n,in[15],f[1<<12][S],t_mp;
bool g[15][15];
char mp[103],rmp[103];
bool pd(char str[]) {
    bool is[13]={0};
    for (int i=0;str[i];++i) {
        is[str[i]-'a']=true;
    }
    int su=0;
    for (int i=0;i<12;++i)
        if (is[i])
            ++su;
    //printf("su=%d\n",su);
    int sp=0,s1=0;
    for (int i=0;i<12;++i) {
        int s = 0;
        for (int j = 0; j < 12; ++j)
            if (g[i][j]) ++s;
        if (s==1) ++s1;
        else if (s!=0 && s!=2) ++sp;
    }
    //printf("%d %d\n",s1,sp);
    if (s1!=2 || sp) return false;
    int id=-1;
    for (int i=0;i<12;++i) {
        int s = 0;
        for (int j = 0; j < 12; ++j)
            if (g[i][j]) ++s;
        if (s==1) {
            id=i;break;
        }
    }
    memset(is,0,sizeof(is));
    t_mp=0;
    while (id!=-1) {
        mp[t_mp++]=id+'a';
        is[id]=true;
        --su;
        int nx=-1;
        for (int j=0;j<12;++j)
            if (g[id][j] && !is[j]) {
                nx = j;
                break;
            }
        id=nx;
    }
    for (int j=0;j<t_mp;++j)
        rmp[t_mp-j-1]=mp[j];
    rmp[t_mp]=mp[t_mp]=0;
    //puts(mp);
    //puts(rmp);
    //printf("%d\n",su);
    return su==0;
}
int top;
int pre_set[1<<12][S],pre_node[1<<12][S];
char pre_c[1<<12][S],res[S];
inline void upd_max(int &a,int b){ a=a>b?a:b; }
void pr(int i,int j){
    if (!i) return;
    pr(pre_set[i][j], pre_node[i][j]);
    res[top++]=pre_c[i][j];
}
int main() {
    scanf("%d",&n);
    char str[S<<1];
    for (int cc,i=1;i<=n;++i) {
        scanf("%d%s",&cc,str);
        memset(g,0,sizeof(g));
        for (int j=1;str[j];++j)
            g[str[j] - 'a'][str[j - 1] - 'a'] = g[str[j - 1] - 'a'][str[j] - 'a'] = true;
        if (pd(str)) {
            insert(mp,cc);
            if (strcmp(rmp,mp))
                insert(rmp,cc);
            //printf("%d %s\n",cc,mp);//puts(mp);
        } else {
            --i;--n;
        }
    }
    build();
    dfs(0);
    for (int i=0;i<(1<<12);++i) {
        for (int j=0;j<=tot;++j)
            f[i][j] = -inf;
    }
    f[0][0] = 0;
    int ans_set=0,ans_node=0,ans=0;
    for (int i=0,lim = 1<<12;i<lim;++i) {
        for (int j=0;j<=tot;++j) {
            if (f[i][j] >= 0) {
                f[i][j]+=c[j];
                //if (i&4 && f[i][j]) printf("f[%d][%d] = %d\n",i,j,f[i][j]);
                if (f[i][j]>ans) {
                    ans=f[i][j];
                    ans_set=i;
                    ans_node=j;
                }
                for (int k = 0; k < 12; ++k)
                    if (!(((i >> k) & 1)) && tr[j][k]) {
                        //printf("%d %d - > %d %d\n",i,j,i|(1<<k),tr[j][k]);
                        if (f[i | (1 << k)][tr[j][k]] < f[i][j]) {
                            f[i | (1<<k)][tr[j][k]] = f[i][j];
                            pre_set[i | (1<<k)][tr[j][k]] = i;
                            pre_node[i | (1<<k)][tr[j][k]] = j;
                            pre_c[i | (1<<k)][tr[j][k]] = k + 'a';
                        }
                    }
            }
        }
    }
    pr(ans_set,ans_node);
    //puts(res);
    bool is[12]={0};
    for (int j=0;j<top;++j)
        is[res[j]-'a'] = true;
    for (int j=0;j<12;++j)
        if (!is[j]) res[top++]=j+'a';
    res[top]=0;
    puts(res);
    return 0;
}