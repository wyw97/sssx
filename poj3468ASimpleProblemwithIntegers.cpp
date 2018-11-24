/*
  http://poj.org/problem?id=3468
  6776 KB
  2668ms
  线段树的模板题，涉及到线段树的插入，区间更新，区间求和，需要注意inc和sum的修改条件
  这道题的一个坑点在于long long int.
*/


#include <iostream>
#include <cstdio>
using namespace std;
struct Node{
    int l;
    int r;
    long long int inc;
    long long int sumn;
}node[400005];
int N,Q;
void Init(int ind, int l, int r)
{
    node[ind].l = l;
    node[ind].r = r;
    node[ind].inc = 0;
    node[ind].sumn = 0;
    if(l == r) return;
    int mid = (l + r)/2;
    Init(ind * 2 + 1, l ,mid);
    Init(ind * 2 + 2, mid + 1, r);
}
void Insert(int ind, int i, int num)
{
    if(node[ind].l == node[ind].r && node[ind].r == i){
        node[ind].sumn = num;
        return;
    }
    node[ind].sumn += num;//easy to be forgotten
    int mid = (node[ind].l + node[ind].r) / 2;
    if(i <= mid){
        Insert(ind * 2 + 1, i, num);
    }
    else{
        Insert(ind * 2 + 2, i, num);
    }
}
void Update(int ind, int l, int r, long long int c)
{
    if(node[ind].l == l && node[ind].r == r){
        node[ind].inc += c;
        return;
    }
    node[ind].sumn += c * (r - l + 1);
    int mid = (node[ind].l + node[ind].r) / 2;
    if(r <= mid){
        Update(ind * 2 + 1, l, r, c);
    }
    else if(l > mid){
        Update(ind * 2 + 2, l, r, c);
    }
    else{
        Update(ind * 2 + 1, l, mid, c);
        Update(ind * 2 + 2, mid + 1, r, c);
    }

}

long long int Query(int ind, int l, int r)
{
    if(node[ind].l == l && node[ind].r == r){
        return node[ind].sumn + (r - l + 1) * node[ind].inc;
    }
    node[ind].sumn += node[ind].inc * (node[ind].r - node[ind].l + 1);
    node[ind * 2 + 1].inc += node[ind].inc;
    node[ind * 2 + 2].inc += node[ind].inc;
    node[ind].inc = 0;
    int mid = (node[ind].l + node[ind].r) / 2;
    if(r <= mid){
        return Query(ind * 2 + 1, l, r);
    }
    else if(l > mid){
        return Query(ind * 2 + 2, l ,r);
    }
    else{
        return Query(ind * 2 + 1, l, mid) + Query(ind * 2 + 2, mid + 1, r);
    }

}
int main()
{
    scanf("%d %d",&N,&Q);
    Init(0, 1, N);
    int temp_num = 0;
    for(int i = 1; i <= N; i++){
        scanf("%d", &temp_num);
        Insert(0, i, temp_num);
    }
    char cmd[10] = {0};
    int l, r, c;
    for(int i = 0 ;i < Q; i++){
        scanf("%s",cmd);
        if(cmd[0] == 'Q'){
            scanf("%d %d", &l, &r);
            printf("%lld\n",Query(0, l, r));
        }
        else if(cmd[0] == 'C'){
            scanf("%d %d %d", &l, &r, &c);
            Update(0, l, r, c);
        }
    }
    return 0;
}
