/*
    http://dapractise.openjudge.cn/2018hwall/015/
    Tarjan算法+拓扑排序
    4104KB
    30ms
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <deque>
#include <queue>
using namespace std;
vector<vector<int> > G;

struct Edge{
    int f;
    int t;
    Edge(int f0 = 0, int t0 = 0):f(f0), t(t0){}
}edge[6005];
int T, n, m;
int f, t;
int Low[1005];
int Dfn[1005];
int NewGroup[1005];
int NewGraph[1005][1005];
int OutPut[1005];
bitset<1005> Road;
int nTimeCount = 1;
deque<int> Stack;
vector<vector<int> > Tuan;
void Tarjan(int u, bitset<1005> road)
{
    Low[u] = Dfn[u] = nTimeCount++;
    Stack.push_back(u);//easy to be forgotton
    int size_u = G[u].size();
    for(int i = 0; i < size_u; ++i){
        int t = G[u][i];
        if(Dfn[t] == 0){
            bitset<1005>newroad = road;
            newroad[t] = 1;
            Tarjan(t, newroad);
            Low[u] = min(Low[u], Low[t]);
        }
        else if(road[t] == 1){
            Low[u] = min(Low[u], Dfn[t]);
        }
    }
    vector<int> ans;
    if(Low[u] == Dfn[u]){
        int v = Stack.back();
        while(v != u){
            ans.push_back(v);
            Stack.pop_back();
            v = Stack.back();
        }
        ans.push_back(v);
        Tuan.push_back(ans);
    }
}
bool TopoSort()
{
    int size_t = Tuan.size();
    deque<int> dq;
    int cnt_zero = 0;
    for(int i = 1; i <= size_t; ++i){
        if(OutPut[i] == 0){
            dq.push_back(i);
            ++cnt_zero;
            //break;
        }
    }
    if(cnt_zero > 1) return false;
    while(!dq.empty()){
        int top_point = dq.front();
        dq.pop_front();
        cnt_zero = 0;
        for(int i = 1; i <= size_t; ++i){
            if(NewGraph[top_point][i] && OutPut[i] == 1){
                dq.push_back(i);
                --OutPut[i];
                cnt_zero++;
            }
        }
        if(cnt_zero > 1) return false;
    }
    return true;
}
int main()
{
    scanf("%d", &T);
    while(T--){
        memset(Low, 0, sizeof(Low));
        memset(Dfn, 0, sizeof(Dfn));
        memset(edge, 0, sizeof(edge));
        memset(OutPut, 0, sizeof(OutPut));
        memset(NewGroup, 0, sizeof(NewGroup));
        memset(NewGraph, 0, sizeof(NewGraph));
        G.clear();
        Tuan.clear();
        Stack.clear();
        Road.reset();
        nTimeCount = 1;
        scanf("%d %d",&n, &m);
        G.resize(n+1);
        for(int i = 0; i < m; ++i){
            scanf("%d %d", &f, &t);
            edge[i].f = f;
            edge[i].t = t;
            G[f].push_back(t);
        }
        for(int i = 1; i <= n; ++i){
            if(Dfn[i] == 0){
                Road.reset();
                Road[i] = 1;
                Tarjan(i,Road);
            }
        }
        int size_t = Tuan.size();//1 —— size_t
        for(int i = 0; i < size_t; ++i){
            int size_st = Tuan[i].size();
            for(int t = 0; t < size_st; t++){
                NewGroup[Tuan[i][t]] = i + 1;
            }
        }
        for(int i = 0; i < m; ++i){
            if(NewGroup[edge[i].f] == NewGroup[edge[i].t]) continue;
            NewGraph[edge[i].f][edge[i].t] = 1;
            OutPut[edge[i].t]++;
        }
        cout<<(TopoSort()?"Yes":"No")<<endl;
    }
    return 0;
}
