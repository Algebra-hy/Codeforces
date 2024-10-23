#include <bits/stdc++.h>
using namespace std;
const int S=600005;
int n,tot;
char a[S];
int c[S],x[S],y[S],rk[S],sa[S],m,h[S],ST[S][20];
void getsa(int n, char a[])
{
    m='z';
    for (int i=1;i<=n;i++)
        ++c[x[i]=a[i]];
    for (int i=1;i<=m;i++)
        c[i]+=c[i-1];
    for (int i=n;i>=1;i--)
        sa[c[x[i]]--]=i;
    for (int o=1;o<=n;o<<=1)
    {
        int top=0;
        for (int i=n-o+1;i<=n;i++)
            y[++top]=i;
        for (int i=1;i<=n;i++)
            if (sa[i]>o)
                y[++top]=sa[i]-o;
        for (int i=1;i<=m;i++)
            c[i]=0;
        for (int i=1;i<=n;i++)
            c[x[i]]++;
        for (int i=1;i<=m;i++)
            c[i]+=c[i-1];
        for (int i=n;i>=1;i--)
            sa[c[x[y[i]]]--]=y[i],y[i]=0;
        for (int i=1;i<=n;i++)
            y[i]=x[i];
        x[sa[1]]=1;
        for (int i=2;i<=n;i++)
            x[sa[i]]=(y[sa[i]]!=y[sa[i-1]] || y[sa[i]+o]!=y[sa[i-1]+o])+x[sa[i-1]];
        m=x[sa[n]];
        if (m==n) break;
    }
}
void geth(int n,char a[])
{
    int k=0;
    for (int i=1;i<=n;i++) rk[sa[i]]=i;
    for (int i=1;i<=n;i++)
    {
        if (rk[i]==1) continue;
        if (k) k--;
        int j=sa[rk[i]-1];
        while (i+k<=n && j+k<=n && a[i+k]==a[j+k]) k++;
        h[rk[i]]=k;
    }
    for (int i=2;i<=n;++i)
        ST[i][0]=h[i];
    for (int j=1;(1<<j)<=(n-1);++j)
        for (int i=2;i + (1<<j) -1<=n;++i)
            ST[i][j]=min(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
}
int i2[S],odd[S],even[S],s2[S];
int query_LCS(int L,int R) { // LCS of 1...L && R..n
    if (L<1 || L>n || R<1 || R>n) return 0;
    int l = tot-L, r = R;
    l = rk[l]; r = rk[r];
    if (l>r) swap(l,r);
    return min(ST[l+1][i2[r-l]],ST[r-(1<<i2[r-l])+1][i2[r-l]]);
}
vector<int> ve_odd[S],ve_even[S];
long long res=0,ans=0;
int ans_id=-1;
char ans_c;
int main() {
    scanf("%d%s",&n,a+1);
    i2[1]=0;
    for (int i=2;i<S;++i) i2[i]=i2[i>>1]+1;
    a[n+1]='$';
    for (int j=1;j<=n;++j)
        a[n+1+j] = a[n-j+1];
    a[tot=2*n+2] = '#';
    getsa(tot,a);
    geth(tot,a);
    //puts(a+1);
    //for (int i=1;i<=tot;++i) printf("%d ",h[i]);puts("h");
    res=0;
    for (int i=1;i<=n;++i) {
        odd[i] = query_LCS(i,i);
        even[i] = query_LCS(i,i+1);
        s2[i-odd[i]+1] ++;
        s2[i+1] -=2;
        s2[i+odd[i]+1] ++;
        s2[i - even[i] + 1]++;
        s2[i + 1]--;
        s2[i + 2]--;
        s2[i + even[i] + 2]++;
        ve_odd[i-odd[i]].push_back(i);
        ve_odd[i+odd[i]].push_back(i);
        ve_even[i-even[i]].push_back(i);
        ve_even[i+even[i]+1].push_back(i);
        res+=odd[i]+even[i];
        //printf("i=%d odd=%d even=%d\n",i,odd[i],even[i]);
    }
    ans=res;ans_id = 1;ans_c = a[1];
    long long su=0,acce=0;
    for (int i=1,j;i<=n;++i) {
        acce+=s2[i];
        su+=acce;
        //printf("%d ",su);
        long long s[26]={0},o;
        for (int id: ve_odd[i]) {
            //printf("odd %d %d\n",i,id);
            j = id + (id-i);
            if (j<1 || j>n) continue;
            s[a[j]-'a']+=1+(i<j?query_LCS(i-1, j+1): query_LCS(j-1,i+1));
        }
        for (int id: ve_even[i]) {
            //printf("even %d %d\n",i,id);
            j = id + (id-i) + 1;
            if (j<1 || j>n) continue;
            s[a[j]-'a']+=1+(i<j?query_LCS(i-1, j+1): query_LCS(j-1,i+1));
        }
        for (int j=0;j<26;++j) {
            o = res-su+odd[i]+s[j];
            if (o>ans) {
                ans_id = i;
                ans_c = j+'a';
                ans = o;
            } else if (o==ans) {
                if (j+'a'<a[i]) {
                    if (ans_c<a[ans_id]) {
                        ;
                    } else {
                        ans_id = i;
                        ans_c = j+'a';
                    }
                } else {
                    if (ans_id<i && ans_c>a[ans_id]) {
                        ans_id = i;
                        ans_c = j+'a';
                    }
                }
            }
        }
    }
    printf("%lld\n",ans);
    for (int i=1;i<=n;++i)
        if (i==ans_id) putchar(ans_c);
        else putchar(a[i]);
    return 0;
}