/*
    http://poj.org/problem?id=3436
    732 KB
    32 ms
    思路：将一台计算机的输入输出看成两个节点
    多一个源和一个汇点，计算机之间如果满足条件则加边
    主要是理解题意quq题干看不懂
    还有Dinic的模板实在是有那么一丁点的长，
    最后输出边不需要顺序，复制一份原图，然后根据原图比较，如果发现
    减少了，则说明被用来进行网络流，减少的量就是网络流中所使用的量。
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <deque>
#include <queue>
using namespace std;
const int MAXN = 99999999;
int N,P;
struct Info{

    vector<int> Input;
    vector<int> Output;
}info[55];
int G[110][110];//0 is the start 2N+1 is the end
int cpy_G[110][110];
int Layer[110];
int Visited[110];
int nMaxFlow = 0;
vector<int> A;
vector<int> B;
vector<int> W;
bool End(int i)
{
    vector<int>::iterator its = info[i].Output.begin();
    while(its != info[i].Output.end()){
        if(*its != 1) return false;
        ++its;
    }
    return true;
}
bool Match(int i, int j)
{
    vector<int>::iterator its1 = info[i].Output.begin();
    vector<int>::iterator its2 = info[j].Input.begin();
    while(its1 != info[i].Output.end()){
        if(*its2 == 0 && *its1 == 1) return false;
        if(*its2 == 1 && *its1 == 0) return false;
        ++its1;
        ++its2;
    }
    return true;
}
bool CountLayer()
{
    int layer = 0;
    deque<int> q;
    memset(Layer,-1,sizeof(Layer));
    Layer[0] = 0;
    q.push_back(0);
    while(!q.empty()){
        int v = q.front();
        q.pop_front();
        for(int j = 0; j <= 2*N+1; j++){
            if(G[v][j] > 0 && Layer[j] == -1){
                Layer[j] = Layer[v] + 1;
                q.push_back(j);
                if(j == 2*N+1) return true;
            }

        }
    }
    return false;
}


int Dinic()
{
    int nflow = 0;
    deque<int> Q;
    while(CountLayer()){
        Q.push_back(0);
        memset(Visited, 0, sizeof(Visited));
        Visited[0] = 1;
        while(!Q.empty()){
            int nd = Q.back();
            if(nd == 2*N + 1){
                int nMinC = MAXN;
                int nMinCvs = 0;
                for(int i = 1; i < Q.size(); i++){
                    int vs = Q[i-1], ve = Q[i];
                    if(G[vs][ve] > 0){
                        if(nMinC > G[vs][ve]){
                            nMinC = G[vs][ve];
                            nMinCvs = vs;
                        }
                    }
                }
                nflow += nMinC;
                for(int i = 1; i < Q.size(); i++){
                    int vs = Q[i-1], ve = Q[i];
                    G[vs][ve] -= nMinC;
                    G[ve][vs] += nMinC;
                }
                while(!Q.empty() && Q.back() != nMinCvs){
                    Visited[Q.back()] = 0;
                    Q.pop_back();
                }
            }
            else{
                int i = 0;
                for(i = 0; i <= 2*N+1; i++){
                    if(G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 && !Visited[i]){
                        Visited[i] = 1;
                        Q.push_back(i);
                        break;
                    }
                }
                if(i > 2*N+1){
                    Q.pop_back();
                }
            }
        }

    }
    return nflow;
}


int main()
{
    scanf("%d %d",&P, &N);
    for(int i = 0; i < N; i++){
        scanf("%d",&G[2*i+1][2*i+2]);
        bool flag = true;
        int temp = 0;
        for(int t = 0; t < P; t++){
            scanf("%d",&temp);
            if(temp == 1) flag = false;
            info[i].Input.push_back(temp);
        }
        if(flag){
            G[0][2*i+1] = MAXN;
        }
        for(int t = 0; t < P; t++){
            scanf("%d",&temp);
            info[i].Output.push_back(temp);
        }
    }
    for(int i = 0; i < N; i++){
        if(End(i)){
            G[2*i+2][2*N+1] = MAXN;
        }
        for(int j = 0; j < N; j++){
            if(Match(i, j)){
                G[2*i+2][2*j+1] = MAXN;
            }
        }
    }
    memcpy(cpy_G, G, sizeof(cpy_G));
    int tmp_size = 0;
    while(tmp_size = Dinic()){
        nMaxFlow += tmp_size;
    }
    int tot_cnt = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(G[2*i+2][2*j+1] < cpy_G[2*i+2][2*j+1]){
                A.push_back(i + 1);
                B.push_back(j + 1);
                W.push_back(cpy_G[2*i+2][2*j+1]-G[2*i+2][2*j+1]);
                ++tot_cnt;
            }
        }
    }
    printf("%d %d\n",nMaxFlow,tot_cnt);
    for(int i = 0; i < tot_cnt; i++){
        printf("%d %d %d\n",A[i], B[i], W[i]);
    }


    return 0;
}
