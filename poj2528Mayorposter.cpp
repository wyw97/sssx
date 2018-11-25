/*
      http://poj.org/problem?id=2528
      41832K
      344ms
1、离散化，把所有的点隔开，注意需要隔开的理由是，比如选择了[3,5][7,8]，离散化后对应的5和7之间需要有空格
2、离散化注意查询的时候找对应坐标-1和+1对应的两个位置，理由如下上面两层选了[1,2]和[3,4]则相当于覆盖率[1,4] 
   故需要把-1 +1两部分全部拿进来
3、在寻找的过程中，需要注意状态的更新，可能在更新完子状态后，自身的状态同样需要更新。
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int C;
int N;
int Size;
int Index[10000005];
struct Info{
    int l;
    int r;
    int is_covered;
}info[160005];
int Node[20005];
struct Range{
    int l;
    int r;
}ran[10005];
void Init(int ind, int l, int r)
{
    info[ind].l = l;
    info[ind].r = r;
    info[ind].is_covered = 0;
    if(l == r){
        return;
    }
    int mid = (l+r)/2;
    Init(ind*2+1, l, mid);
    Init(ind*2+2, mid+1, r);
}
bool Query(int ind, int l, int r)
{
    if(info[ind].is_covered) return true;
    if(info[ind].l == l && info[ind].r == r){
        info[ind].is_covered = 1;
        return false;
    }

    int mid = (info[ind].l + info[ind].r) / 2;
    int ret = 0;
    if(r <= mid){
        ret = Query(ind * 2 + 1, l, r);
    }
    else if(l > mid){
        ret = Query(ind * 2 + 2, l, r);
    }
    else{
        int r1 = Query(ind * 2 + 1, l, mid), r2 = Query(ind * 2 + 2, mid + 1, r);
        ret = r1 & r2;
    }
    info[ind].is_covered = (info[ind*2+1].is_covered) & info[ind*2+2].is_covered;
    return ret;
}
int main()
{
    scanf("%d",&C);
    for(int i = 0; i < C; i++){
        memset(Index, -1, sizeof(Index));
        memset(info, 0, sizeof(info));
        memset(Node, 0, sizeof(Node));
        memset(ran, 0, sizeof(ran));
        scanf("%d", &N);
        Init(0, 0, 4*N + 1);
        int l = 0, r = 0;
        for(int t = 0; t < N; t++){
            scanf("%d %d", &l, &r);
            ran[t].l = l;
            ran[t].r = r;
            Node[2*t] = l;
            Node[2*t + 1] = r;
        }
        sort(Node, Node + 2*N);
        Size = unique(Node, Node + 2*N) - Node;
        for(int t = 0; t < Size; t++){
            Index[Node[t]] = 2*t + 1;
        }
        int tot_cnt = 0;
        for(int t = N - 1; t >= 0; t--){
            if(!Query(0, Index[ran[t].l] - 1, Index[ran[t].r] + 1)){
                tot_cnt++;
            }
        }
        printf("%d\n", tot_cnt);

    }
    return 0;
}
