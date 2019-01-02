/*
    12072KB
    577ms
    Disktra模板题，用优先队列实现.
    http://bailian.openjudge.cn/practice/3424/

*/
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;
struct Node{
    int t;
    int w;
    Node(int t0 = 0, int w0 = 0):t(t0), w(w0){}
};

bool operator < (const Node& n1, const Node& n2)
{
    return n1.w > n2.w;
}
priority_queue<Node> pq;
vector<vector<Node> > G;
int N, M;
int A, B, c;
bitset<30005>Used;
int main()
{
    scanf("%d %d", &N, &M);
    Node nt;
    G.clear();
    G.resize(N+1);
    Used.reset();
    for(int i = 0; i < M; ++i){
        scanf("%d %d %d", &A, &B, &c);
        nt.t = B;
        nt.w = c;
        G[A].push_back(nt);
        //pq.push(nt);
    }
    nt.t = 1;
    nt.w = 0;
    pq.push(nt);
    Node topo;
    while(!pq.empty()){
        topo = pq.top();
        pq.pop();
        if(Used[topo.t]) continue;
        if(topo.t == N) break;
        Used[topo.t] = 1;
        int size_t = G[topo.t].size();
        for(int i = 0; i < size_t; i++){
            if(Used[G[topo.t][i].t] == 1) continue;
            int new_t = G[topo.t][i].t;
            int new_w = G[topo.t][i].w + topo.w;
            pq.push(Node(new_t, new_w));

        }
    }
    printf("%d\n", topo.w);
    return 0;
}
