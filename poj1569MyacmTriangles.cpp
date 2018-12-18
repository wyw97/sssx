/*
http://poj.org/problem?id=1569
0ms
计算几何，判断点是否在多边形内，叉积即可。
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
struct CPoint{
    double x;
    double y;
    CPoint(){
        x = y = 0.0;
    }
    CPoint(double x0, double y0){
        x = x0;
        y = y0;
    }
};
struct Info{
    char c;
    double x;
    double y;
    Info(){
        c = ' ';
        x = y = 0.0;
    }
    Info(char c0, double x0, double y0){
        c = c0;
        x = x0;
        y = y0;
    }
};
Info info[18];
int N;
double operator ^ (CPoint c1, CPoint c2)
{
    return c1.x * c2.y - c1.y * c2.x;
}
double operator * (CPoint c1, CPoint c2)
{
    return c1.x * c2.x + c1.y * c2.y;
}
int Judge(CPoint p1, CPoint p2)
{
    double res = p1 ^ p2;
    if(res > 0) return 1;
    else if (res < 0) return -1;
    double cor = p1 * p2;
    if(cor < 0) return 4;
    if(cor > p1 * p1) return 4;
    else return 0;
}

int main()
{
    while(scanf("%d", &N)){
        if(!N) break;
        memset(info, 0, sizeof(info));
        for(int i = 0; i < N; i++){
            cin>>info[i].c>>info[i].x>>info[i].y;
        }
        int max0 = 0, max1 = 0, max2 = 0, maxarea = 0;
        for(int i = 0; i < N; i++){
            for(int j = i + 1; j < N; j++){
                for(int k = j + 1; k < N; k++){
                    CPoint p1(info[j].x - info[i].x, info[j].y - info[i].y);
                    CPoint p2(info[k].x - info[j].x, info[k].y - info[j].y);
                    CPoint p3(info[i].x - info[k].x, info[i].y - info[k].y);
                    double res1 = 0.0, res2 = 0.0, res3 = 0.0;
                    if((res1 = (p1 ^ p2)) == 0) continue;
                    if((res2 = (p2 ^ p3)) == 0) continue;
                    if((res3 = (p3 ^ p1)) == 0) continue;
                    bool flag = true;
                    for(int t = 0; t < N; t++){
                        if(t == i) continue;
                        if(t == j) continue;
                        if(t == k) continue;
                        CPoint t1(info[t].x - info[i].x, info[t].y - info[i].y);
                        CPoint t2(info[t].x - info[j].x, info[t].y - info[j].y);
                        CPoint t3(info[t].x - info[k].x, info[t].y - info[k].y);
                         int cnt_sig = 0, tot_cnt = 0;
                        cnt_sig = Judge(p1, t1);
                        if(cnt_sig == 0){
                            flag = false;
                            break;
                        }
                        else if(cnt_sig == 4){
                            continue;
                        }
                        else{
                            tot_cnt += cnt_sig;
                        }
                        cnt_sig = Judge(p2, t2);
                        if(cnt_sig == 0){
                            flag = false;
                            break;
                        }
                        else if(cnt_sig == 4){
                            continue;
                        }
                        else{
                            tot_cnt += cnt_sig;
                        }
                        cnt_sig = Judge(p3, t3);
                        if(cnt_sig == 0){
                            flag = false;
                            break;
                        }
                        else if(cnt_sig == 4){
                            continue;
                        }
                        else{
                            tot_cnt += cnt_sig;
                        }
                        if(tot_cnt == 3 || tot_cnt == -3){
                            flag = false;
                            break;
                        }
                    }
                    if(flag){
                        double temp_area = fabs(p1 ^ p2) / 2;
                        if(temp_area > maxarea){
                            maxarea = temp_area;
                            max0 = i, max1 = j, max2 = k;
                        }
                    }


                }
            }
        }
        char reschar[4] = {0};
        reschar[0] = info[max0].c;
        reschar[1] = info[max1].c;
        reschar[2] = info[max2].c;
        sort(reschar, reschar + 3);
        for(int t = 0; t < 3; t++){
            printf("%c", reschar[t]);
        }
        printf("\n");
    }
    return 0;
}
