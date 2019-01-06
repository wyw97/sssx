/*
    http://poj.org/problem?id=1860
    标准模板题，不过是反过来寻找存在正的环就可以了。
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
using namespace std;
int N, M, S;
double V;
struct Info{
    int f;
    int t;
    double r;
    double c;
    Info(int f0 = 0, int t0 = 0, double r0 = 0, double c0 = 0):f(f0),t(t0),r(r0),c(c0){}
};
int A, B;
double Rab, Rba, Cab, Cba;
vector<Info> Edge;
double Money[105];
int BF()
{
    Money[S] = V;
    int size_e = Edge.size();
    for(int i = 1; i < N; ++i){
        for(int t = 0; t < size_e; ++t){
            if(Money[Edge[t].t] < (Money[Edge[t].f]-Edge[t].c)*Edge[t].r){
                Money[Edge[t].t] = (Money[Edge[t].f]-Edge[t].c)*Edge[t].r;
            }
        }
    }
    for(int t = 0; t < size_e; ++t){
        if(Money[Edge[t].t] < (Money[Edge[t].f]-Edge[t].c)*Edge[t].r){
            return true;
        }
    }
    return false;
}
int main()
{
    scanf("%d%d%d%lf", &N, &M, &S, &V);
    for(int i = 0; i < M; ++i){
        scanf("%d%d%lf%lf%lf%lf", &A, &B,&Rab, &Cab, &Rba, &Cba);
        Edge.push_back(Info(A,B,Rab,Cab));
        Edge.push_back(Info(B,A,Rba,Cba));
    }
    cout<<(BF()?"YES":"NO")<<endl;
     return 0;
}
