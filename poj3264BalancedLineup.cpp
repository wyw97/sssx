/*
  http://poj.org/problem?id=3264
  线段树的模板题
  2668KB
  3485MS
  涉及单个点的插入，区间的查询。
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int N, Q;
struct Info{
    int L;
    int R;
    int Maxn;
    int Mini;
}info[200005];
int maxn = 0, mini = 999999;
void Build(int ind, int l, int r)
{
    if(l == r){
        info[ind].R = info[ind].L = l;
        info[ind].Maxn = 0;
        info[ind].Mini = 9999999;
        return;
    }
    int mid = (l + r)/2;
    info[ind].L = l;
    info[ind].R = r;
    Build(ind * 2 + 1, l, mid);
    Build(ind * 2 + 2, mid + 1, r);
    info[ind].Mini = 9999999;
    info[ind].Maxn = 0;
}
void Insert(int ind, int num, int height)
{
    if(info[ind].L == info[ind].R && info[ind].R == num){
        info[ind].Maxn = info[ind].Mini = height;
        return;
    }
    int mid = (info[ind].L + info[ind].R) / 2;
    if(num <= mid){
        Insert(ind * 2 + 1, num, height);
    }
    else{
        Insert(ind * 2 + 2, num, height);
    }
    info[ind].Mini = min(info[ind*2+1].Mini,info[ind*2+2].Mini);
    info[ind].Maxn = max(info[ind*2+1].Maxn,info[ind*2+2].Maxn);
}
void Query(int ind, int L, int R)
{
    if(info[ind].Mini >= mini && info[ind].Maxn <= maxn) return;
    if(info[ind].L == L && info[ind].R == R){
        mini = min(mini, info[ind].Mini);
        maxn = max(maxn, info[ind].Maxn);
        return;
    }
    int mid = (info[ind].L + info[ind].R)/2;
    if(R <= mid){
        Query(ind*2+1, L, R);
    }
    else if(L > mid){
        Query(ind*2+2, L, R);
    }
    else{
        Query(ind*2+1, L, mid);
        Query(ind*2+2, mid+1, R);
    }


}
int main()
{
    scanf("%d %d",&N, &Q);
    Build(0, 1, N);
    int height;
    for(int i = 1; i <= N; i++){
        scanf("%d", &height);
        Insert(0, i, height);
    }
    int L, R;
    for(int i = 0; i < Q; i++){
        scanf("%d %d", &L, &R);
        maxn = 0;
        mini = 9999999;
        Query(0, L, R);
        printf("%d\n", maxn - mini);
    }
    return 0;
}
