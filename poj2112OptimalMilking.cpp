/*
      http://poj.org/problem?id=2112
       1092KB
       141MS
       学会构建网络流，并利用floyd求出最短路径。
       网络流的题目是真**的长啊。
       源和汇分别设置，把牛和奶站分开看即可，寻找最长的边的时候可以考虑采用二分法。
       我感觉我的算法似乎有一点bug，但是poj上也ac了，可能是数据弱吧，正常来讲，应该是去到了一条最长边后，
       这条边应该只有一条边连接到奶站了，哎，我也不懂。
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
using namespace std;
const int MAXN = 9999999;
int Dis[235][235];
int G[235][235];
int DisLast[7005];
int Layer[235];
int Visited[235];
int K, C, M;
void Floyd()
{
    int size_matrix = K + C;
    for(int k = 1; k <= size_matrix; k++){
        for(int i = 1; i <= size_matrix; i++){
            for(int j = 1; j <= size_matrix; j++){
                Dis[i][j] = min(Dis[i][j], Dis[i][k] + Dis[k][j]);
            }
        }
    }
}
bool CountLayer()
{
    deque<int> q;
    memset(Layer, -1, sizeof(Layer));
    Layer[0] = 0;
    q.push_back(0);
    while(!q.empty()){
        int v = q.front();
        q.pop_front();
        for(int j = 0; j <= K + C + 1; j++){
            if(G[v][j] > 0 && Layer[j] == -1){
                Layer[j] = Layer[v] + 1;
                q.push_back(j);
                if(j == K + C + 1) return true;
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
            if(nd == K + C + 1){
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
                for(i = 0; i <= K + C + 1; i++){
                    if (G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 && !Visited[i]){
                        Visited[i] = 1;
                        q.push_back(i);
                      //  printf("i: %d\n", i);
                        break;

                    }
                }
                if(i > K + C + 1){//没找到合适的点;
                    q.pop_back();
                }
            }
        }//栈非空
    }
    return nMaxFlow;
}
int main() {
    memset(Dis, 0, sizeof(Dis));
    memset(DisLast, 0, sizeof(DisLast));
    scanf("%d %d %d", &K, &C, &M);
    for (int i = 1; i <= K + C; i++) {
        for (int j = 1; j <= K + C; j++) {
            scanf("%d", &Dis[i][j]);
            if (!Dis[i][j] && i != j) {
                Dis[i][j] = MAXN;
            }
        }
    }
    Floyd();
    /*
    for (int i = 1; i <= K + C; i++) {
        for (int j = 1; j <= K + C; j++) {
            cout << Dis[i][j] << " ";
        }
        cout << endl;

    }
     */
    int totCountDis = 0;
    for(int i = K + 1; i <= K + C; i++){
        for (int t = 1; t <= K; t++) {
            DisLast[totCountDis] = Dis[i][t];
            totCountDis++;
        }
    }
    sort(DisLast, DisLast + totCountDis);
    /*
    for(int i = 0; i < totCountDis; i++){
        printf("Sort: %d %d\n",i, DisLast[i]);
    }
    */
    int begNum = 0, endNum = totCountDis - 1, mid = (begNum + endNum) / 2;
    //printf("beg: %d ,end: %d  ,mid: %d\n", begNum, endNum, mid);
    int nMaxFlow = 0, minMax = MAXN;
    while(true){
        memset(G, 0, sizeof(G));
        nMaxFlow = 0;

        int tempMin = DisLast[mid];
        for(int i = K + 1; i <= K + C; i++){
            for(int j = 1; j <= K; j++){
                if(Dis[i][j] <= tempMin){
                    G[i][j] = 1;
                }
            }
        }
        for(int i = K + 1; i <= K + C; i++){
            G[0][i] = 1;
        }
        for(int i = 1; i <= K; i++){
            G[i][K + C + 1] = M;
        }
       nMaxFlow = Dinic();
       if(nMaxFlow == C){
            minMax = tempMin;
            endNum = mid - 1;
        }
        else{
            begNum = mid + 1;
        }
        if(begNum > endNum) break;
        mid = (begNum + endNum) / 2;
    }
    printf("%d\n", minMax);
    return 0;
}
