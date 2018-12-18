/*
  http://bailian.openjudge.cn/practice/1269/
  128KB
  1ms
  emmm不知道为啥poj上过不去，openjudge上可以，懒得改了，这里用了gw老师课件上的算法
  还不如直接求来的快，判断是否平行就行了。

*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
struct CPoint{
    double x;
    double y;
    CPoint(){
        x = 0.0;
        y = 0.0;
    }
    CPoint(double x0, double y0){
        x = x0;
        y = y0;
    }
};
CPoint operator + (CPoint p1, CPoint p2){
    return CPoint(p1.x + p2.x, p1.y + p2.y);
}
CPoint operator - (CPoint p1, CPoint p2){
    return CPoint(p1.x - p2.x, p1.y - p2.y);
}
double operator ^ (CPoint p1, CPoint p2){
    return p1.x * p2.y - p1.y * p2.x;
}
CPoint operator * (CPoint p, double k)
{
    return CPoint(p.x * k, p.y * k);
}
bool isZero(double num)
{
    if(fabs(num) <= 1e-4){
        return true;
    }
    else return false;
}
int N;
CPoint Point[4];
double TriangleArea(CPoint c1, CPoint c2){
    return (c1^c2)/2;
}
int mycmp(const CPoint& c1, const CPoint& c2){
    return (c1.x < c2.x) || (c1.x == c2.x && c1.y < c2.x);
}
double DisPoint(CPoint c1, CPoint c2){
    CPoint c = c1 - c2;
    return sqrt(pow(c.x, 2.0) + pow(c.y, 2.0));
}

int main()
{
    scanf("%d", &N);
    printf("INTERSECTING LINES OUTPUT\n");
    for(int i = 0; i < N; i++){
        for(int t = 0; t < 4; t++){
            scanf("%lf %lf", &Point[t].x, &Point[t].y);
        }
        sort(Point, Point + 2, mycmp);
        sort(Point + 2, Point + 4, mycmp);
        double x = TriangleArea(Point[2] - Point[0], Point[1] - Point[0]);
        double y = TriangleArea(Point[1] - Point[0], Point[3] - Point[0]);
       //cout<<x<<','<<y<<endl;
        if(isZero(x + y)){
            CPoint c1 = Point[0] - Point[2];
            CPoint c2 = Point[1] - Point[2];
            if(isZero(2*TriangleArea(c1, c2)/DisPoint(Point[0], Point[1]))){
                printf("LINE\n");
            }
            else printf("NONE\n");

        }
        else{
            //CPoint c_temp = Point[2] * 2;
           // cout<<c_temp.x << " "<<c_temp.y <<endl;
            CPoint c_int = Point[2] + (Point[3] - Point[2]) * (x / (x + y));
            printf("POINT %.2lf %.2lf\n", c_int.x, c_int.y);
        }
    }

    printf("END OF OUTPUT\n");
    return 0;
}
