/*
  http://poj.org/problem?id=3321
  13092K
  1297MS
  苹果树，思路比较新颖，通过记录树上每个节点深度优先搜索时
  进入和离开的时间，则在该区间的是该节点及其全部子节点
  在poj上卡时比较严格，需要注意以下两点；
  1. vector<vector<int> > V(100005),直接这样初始化
  2. char c[2];scanf("%s",c);
*/

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
int N;

int BeginNum[100005];
int EndNum[100005];
int Cnt[200005];
int Visited[100005];
 /*
vector<int> BeginNum;
vector<int> EndNum;
vector<int> Cnt;
vector<int> Visited;
  */
vector<vector<int> >Tree(100005);
int tot_num = 1;
void Build(int ind)
{
    Visited[ind] = 1;
    BeginNum[ind] = tot_num;
    tot_num++;

    int tmp_size = Tree[ind].size();
    if(tmp_size) {
        for (int t = 0; t < tmp_size; t++) {
            if(!Visited[Tree[ind][t]])
                Build(Tree[ind][t]);
        }
    }
    EndNum[ind] = tot_num;
    tot_num++;
}
int lowbit(int x){
    return x & (-x);
}
int sumn(int i){
    int cnt = 0;
    while(i > 0){
        cnt += Cnt[i];
        i -= lowbit(i);
    }
    return cnt;
}
void Update(int i,int num){
    while( i <= 2*N){
        Cnt[i] += num;
        i += lowbit(i);
    }

}
int main()
{
    scanf("%d",&N);
   \
    Visited[0] = 0;
    int u,v;
    for(int i = 1; i < N; i++){
        scanf("%d %d",&u,&v);
        Tree[u].push_back(v);
    };
    Build(1);
    for(int i = 1; i <= 2*N; i++){
        Cnt[i] = lowbit(i);
    }
    /*
    for(int i = 1; i <= 2*N ;i++) {
        cout<<i<<" : "<<Cnt[i]<<endl;
    }
    */
    int M = 0;
    scanf("%d",&M);
    char c[2];
    int num;
    for(int t = 0; t < M; t++){
        scanf("%s %d",c,&num);//cin>>c>>num;
        if(c[0] == 'Q'){
            printf("%d\n",(sumn(EndNum[num])-sumn(BeginNum[num]-1))/2);
        }
        else{
            int beg = BeginNum[num], end_ = EndNum[num];
            Visited[num] = 1 - Visited[num];

            int minu = 2 * Visited[num] - 1;
            Update(beg,minu);
            Update(end_,minu);
        }
    }
    return 0;
}
