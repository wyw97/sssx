/*
  http://poj.org/problem?id=1274
  1274K
  16ms
  二部图匹配的问题，模版题
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
const int MAXN = 9999999;
int G[405][405];
int Layer[405];
int Visited[405];
int N, M;

bool CountLayer()
{
    deque<int> q;
    memset(Layer, -1, sizeof(Layer));
    Layer[0] = 0;
    q.push_back(0);
    while(!q.empty()){
        int v = q.front();
        q.pop_front();
        for(int j = 0; j <= M + N + 1; j++){
            if(G[v][j] > 0 && Layer[j] == -1){
                Layer[j] = Layer[v] + 1;
                q.push_back(j);
                if(j == M + N + 1) return true;
            }
        }

    }
    return false;
}
int Dinic()
{
    int nMaxFlow = 0;
    deque<int> q;
    while(CountLayer()){
        // printf("Circle\n");
        q.push_back(0);
        memset(Visited, 0, sizeof(Visited));
        Visited[0] = 1;
        while(!q.empty()){
            int nd = q.back();
            // printf("nd %d\n", nd);
            if(nd == M + N + 1){
                // nd 是 汇点
                int nMinC = MAXN;
                int nMinC_vs;//最小容量边的起点;
                for(int i = 1; i < q.size(); i++){
                    int vs = q[i-1];
                    int ve = q[i];
                    if(G[vs][ve] > 0){
                        if(nMinC > G[vs][ve]){
                            nMinC = G[vs][ve];
                            nMinC_vs = vs;
                        }
                    }
                }
                // printf("nMinc: %d\n", nMinC);
                nMaxFlow += nMinC;
                for(int i = 1; i < q.size(); i++){
                    int vs = q[i-1];
                    int ve = q[i];
                    G[vs][ve] -= nMinC;
                    G[ve][vs] += nMinC;//添加反向边;
                }
                while(!q.empty() && q.back() != nMinC_vs){
                    Visited[q.back()] = 0;
                    q.pop_back();
                }
            }//汇点
            else{
                int i = 0;
                for(i = 0; i <= M + N + 1; i++){
                    if (G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 && !Visited[i]){
                        Visited[i] = 1;
                        q.push_back(i);
                        //  printf("i: %d\n", i);
                        break;

                    }
                }
                if(i > M + N + 1){//没找到合适的点;
                    q.pop_back();
                }
            }
        }//栈非空
    }
    return nMaxFlow;
}
int main() {

    while(scanf("%d %d", &N, &M) != EOF){
        if(!M && !N) break;
        memset(G, 0, sizeof(G));
        memset(Layer, 0, sizeof(Layer));
        memset(Visited, 0, sizeof(Visited));
        int tempLen = 0, tempNum = 0;
        for(int i = 1; i <= N; i++){
            scanf("%d", &tempLen);
            for(int t = 1; t <= tempLen; t++){
                scanf("%d", &tempNum);
                G[i][N + tempNum] = 1;
            }
        }
        for(int i = 1; i <= N; i++){
            G[0][i] = 1;
        }
        for(int i = N + 1; i <= N + M; i++){
            G[i][N + M + 1] = 1;
        }
        printf("%d\n", Dinic());
    }
    return 0;
}
