/*
http://bailian.openjudge.cn/practice/solution/17253570/
384kB
22ms
选择一上一下的两个点计算即可，但是问题是在poj上过不去QAQ
i和j从0开始取就好了，开始的时候wa的原因是考虑i下j上或者i上j下，但是不知道为啥一直wa
莫名其妙的骗过了openjudge，有空再改吧。。。
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
struct CPoint{
    double x;
    double y;
    CPoint(double x0 = 0.0, double y0 = 0.0):x(x0), y(y0){}

}cpoint[25];
int N;
const double EXP = 1e-6;
int JudgeZero(double d)
{
    if(fabs(d) <= EXP){
        return 0;
    }
    if(d > 0) return 1;
    else return -1;
}
double operator ^ (CPoint c1, CPoint c2)
{
    return c1.x * c2.y - c2.x * c1.y;
}
CPoint operator - (CPoint c1, CPoint c2)
{
    return CPoint(c1.x - c2.x, c1.y - c2.y);
}
int main()
{
    while(scanf("%d", &N)){
        if(!N) break;
        for(int i = 0; i < 25; i++){
            cpoint[i].x = cpoint[i].y = 0.0;
        }
        for(int i = 0; i < N; i++){
            scanf("%lf %lf", &cpoint[i].x, &cpoint[i].y);
        }
        double maxDis = cpoint[1].x;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(j == i) continue;
                //i down j up
                double dx = cpoint[j].x - cpoint[i].x;
                double dy = cpoint[j].y - cpoint[i].y + 1;
                for(int t = 0; t < N; t++){
                    double xt = cpoint[t].x;
                    double yt = ((cpoint[t].x - cpoint[i].x) * dy / dx) + cpoint[i].y - 1;
                    CPoint ct(xt, yt);
                    if(JudgeZero(yt - cpoint[t].y) == 1){
                        if(!t) break;
                        CPoint cid(cpoint[i].x, cpoint[i].y - 1);
                        double S1 = (ct - cid) ^ (cpoint[t-1] - cid);
                        double S2 = (cpoint[t] - cid) ^ (ct - cid);
                        double xReach = cpoint[t-1].x + (cpoint[t].x - cpoint[t-1].x) * S1 / (S1 + S2);
                        maxDis = max(xReach, maxDis);
                        break;
                    }
                    else if(JudgeZero(yt - (cpoint[t].y - 1)) == -1){
                        if(!t) break;
                        CPoint ctd(cpoint[t].x, cpoint[t].y - 1);
                        CPoint ctmd(cpoint[t-1].x, cpoint[t-1].y - 1);
                        CPoint cid(cpoint[i].x, cpoint[i].y - 1);
                        double S1 = (ctd - ctmd) ^ (cid - ctmd);
                        double S2 = (ct - ctmd) ^ (ctd - ctmd);
                        double xReach = cpoint[i].x + (cpoint[t].x - cpoint[i].x) * S1 / (S1 + S2);
                        maxDis = max(xReach, maxDis);
                        break;
                    }
                    else{
                        maxDis = max(maxDis, cpoint[t].x);
                    }
                }
            }
        }
        if(JudgeZero(maxDis - cpoint[N-1].x) == 0){
            printf("Through all the pipe.\n");
        }
        else{
            printf("%.2lf\n", maxDis);
        }


    }
    return 0;
}
