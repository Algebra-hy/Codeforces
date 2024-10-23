#include <cstdio>
#include "algorithm"
using namespace std;
const int S=1003;
int n,la[S];
char c[S];
struct node {
    int pos,id;
}b[S];
int tot;
inline bool cmp(const node &a,const node &b) {
    return a.pos<b.pos;
}
int main() {
    scanf("%d",&n);
    for (int i=0;i<26;++i)b[i]=(node){0,i};
    tot=0;
    for (int i=1;i<=n;++i) {
        printf("? 2 %d %d\n",1,i);
        fflush(stdout);
        int o;
        scanf("%d",&o);
        int l=0,r=tot,mid;
        while (l<r) {
            mid=(l+r)>>1;
            printf("? 2 %d %d\n",b[mid].pos+1,i);
            fflush(stdout);
            int y;scanf("%d",&y);
            //printf("== y=%d mid=%d(%d) o=%d\n",y,mid,b[mid].pos,o);
            if (y+mid+1!=o) r=mid;
            else l=mid+1;
        }
        if (l==tot) b[tot]=(node){i,tot},++tot;
        else {
            la[i] = b[l].pos;
            b[l].pos = i;
        }
        sort(b, b + tot, cmp);
    }
    for (int i=0;i<tot;++i) {
        printf("? 1 %d\n",b[i].pos);
        fflush(stdout);
        char o[3];scanf("%s",o);
        for (int j=b[i].pos;j;j=la[j])
            c[j] = o[0];
    }
    printf("! %s\n",c+1);
    //for (int i=1;i<=n;++i) printf("%d ",la[i]);puts("la");
    fflush(stdout);
}