/*
    http://bailian.openjudge.cn/practice/2186/
    把强连通分量合并
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <bitset>
using namespace std;
int N, M, A, B;
vector<vector<int> > G;
vector<vector<int> > Tuan;
deque<int> Stack;
vector<int> Visited;
vector<int> DFN;
vector<int> LOW;
vector<int> OutPut;
vector<int> InPut;
vector<int> NewGroup;
int nTime = 1;
void Tarjan(int u, bitset<10005> Road)
{
    DFN[u] = LOW[u] = nTime++;
    Stack.push_back(u);
    int size_u = G[u].size();
    for(int i = 0; i < size_u; ++i){
        int v = G[u][i];
        if(DFN[v] == 0){
            bitset<10005> CpyRoad = Road;
            CpyRoad[v] = 1;
            Tarjan(v, CpyRoad);
            LOW[u] = min(LOW[u], LOW[v]);
        }
        else if(Road[v] == 1){
            LOW[u] = min(LOW[u], DFN[v]);
        }
    }
    if(DFN[u] == LOW[u]){
        int topo = Stack.back();
        Stack.pop_back();
        vector<int> TempAns;
        TempAns.push_back(topo);
        while(topo != u){
            topo = Stack.back();
            Stack.pop_back();
            TempAns.push_back(topo);
        }
        Tuan.push_back(TempAns);
    }
}
int main()
{
    scanf("%d %d", &N, &M);
    G.clear();
    G.resize(N + 1);
    Visited.resize(N + 1);
    DFN.resize(N + 1);
    LOW.resize(N + 1);
    NewGroup.resize(N + 1);
    for(int i = 0; i < M; ++i){
        scanf("%d %d", &A, &B);
        G[A].push_back(B);
    }
    for(int i = 1; i <= N; ++i){
        if(DFN[i]) continue;
        bitset<10005>Road;
        Road.reset();
        Road[i] = 1;
        Tarjan(i, Road);
    }
    int ng_size = Tuan.size();
    OutPut.resize(ng_size);
    InPut.resize(ng_size);
    for(int i = 0; i < ng_size; ++i){
        int size_new_t = Tuan[i].size();
        for(int j = 0; j < size_new_t; j++){
            NewGroup[Tuan[i][j]] = i;
        }
    }
    for(int i = 1; i <= N; ++i){
        int size_g_temp = G[i].size();
        for(int t = 0; t < size_g_temp; t++){
            int v = G[i][t];
            if(NewGroup[v] != NewGroup[i]){
                OutPut[NewGroup[i]]++;
                InPut[NewGroup[v]]++;
            }
        }
    }
    int tot = 0, cnt = 0;
    for(int i = 0; i < ng_size; ++i){
        if(OutPut[i] == 0){
            ++cnt;
            tot += Tuan[NewGroup[i]].size();
        }
    }
    cout<<((cnt == 1)?tot:0)<<endl;
    return 0;
}
