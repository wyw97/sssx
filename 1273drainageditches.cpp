/*
  http://bailian.openjudge.cn/practice/1273/
  256 KB
  4ms
  标准模板题，注意输入scanf eof即可
  还有，注意边可能重复两次输入，所以要相加。
*/
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int G[205][205];
int Visited[205];
int Prev[205];

int N, M;
int Karp()
{
    memset(Visited,0,sizeof(Visited));
    memset(Prev,0,sizeof(Prev));
    Visited[1] = 1;
    Prev[1] = 0;
    bool fndEndPoint = false;
    queue<int> Q;
    Q.push(1);
    while(!Q.empty()){
        int beg_num = Q.front();
        Q.pop();
        for(int i = 1; i <= M; i++){
            if(!Visited[i] && G[beg_num][i]){
                Q.push(i);
                Visited[i] = 1;
                Prev[i] = beg_num;

                if( i == M ){
                    fndEndPoint = true;
                    while(!Q.empty()){
                        Q.pop();
                    }
                    break;
                }

            }
        }
    }
    if(fndEndPoint == false) return 0;
    int end_num = M, min_flow = 99999999;
    while(Prev[end_num]){
        min_flow = min(min_flow, G[Prev[end_num]][end_num]);
        end_num = Prev[end_num];
    }
    end_num = M;
    while(Prev[end_num]){
        int p = Prev[end_num];
        G[p][end_num] -= min_flow;
        G[end_num][p] += min_flow;
        end_num = p;
    }
    return min_flow;
}
int main()
{
    while(scanf("%d %d",&N, &M)!=EOF) {
        //cin >> N >> M;
        memset(Prev,0,sizeof(Prev));
        memset(Visited,0,sizeof(Visited));
        memset(G,0,sizeof(G));
        int E = 0, C = 0, S = 0;
        for(int i = 0 ; i < N; i++){
            scanf("%d %d %d", &S, &E, &C);
            G[S][E] += C;
        }
        int cnt_tot = 0;
        int temp_add = 0;
        while(temp_add = Karp()){
            cnt_tot += temp_add;
        }
        printf("%d\n",cnt_tot);
    }
    return 0;
}
