/*
http://bailian.openjudge.cn/practice/1228/
128kB
3ms
wa的原因可能是零的精度问题，用水平角凸包模板即可。
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
#include <queue>
using namespace std;
const int EXP = 1e-8;
struct Point{
    double x;
    double y;
    Point(double x0 = 0.0, double y0 = 0.0):x(x0), y(y0){}
}point[1005];
int T;
int N;
int Sign(double f1, double f2)
{
    if(fabs(f1 - f2) <= EXP) return 0;
    else if(f1 < f2) return -1;
    else return 1;
}
int cmp(const Point& p1, const Point& p2)
{
    return (Sign(p1.x, p2.x) == -1) || (Sign(p1.x, p2.x) == 0 && Sign(p1.y, p2.y) == -1);
    //return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
}
Point operator -(const Point& p1, const Point p2)
{
    return Point(p1.x - p2.x, p1.y - p2.y);
}
double Cross(Point p1, Point p2)
{
    return p1.x * p2.y - p2.x * p1.y;
}
double operator * (const Point& p1, const Point& p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}
deque<Point> Stack;
int main()
{
    scanf("%d", &T);
    while(T--){
        memset(point, 0, sizeof(point));
        Stack.clear();
        scanf("%d", &N);
        for(int i = 0; i < N; ++i) {
            scanf("%lf %lf", &point[i].x, &point[i].y);
        }
        if(N < 6){
            printf("NO\n");
            continue;
        }
        sort(point, point + N, cmp);
        Stack.push_back(point[0]);
        Stack.push_back(point[1]);

        for(int i = 2; i< N; ++i) { //做右半凸包
            while(Stack.size()>1)	{//定要这一条
                Point p2 = * (Stack.end()-1);
                Point p1 = * (Stack.end()-2);
                if( Sign(Cross(p2-p1,point[i]-p2), 0.0) <= 0) {
                    //p2->points[i]向右转，才让p2出栈 ，这样能保留凸包边上的点
                    Stack.pop_back();
                }
                else
                    break;
            }
            Stack.push_back(point[i]);
        }

        int size_s = Stack.size();
        Stack.push_back(point[N-2]);
        for(int i = N-3; i >= 0;--i) { //做左半凸包
            while(Stack.size() > size_s) {
                Point p2 = * (Stack.end()-1);
                Point p1 = * (Stack.end()-2);
                if( Sign(Cross(p2-p1,point[i]-p2) ,0.0) <= 0)
                    Stack.pop_back();
                else
                    break;
            }
            Stack.push_back(point[i]);
        }
        Stack.pop_back();

        size_s = Stack.size();
        if(size_s < 3){
            printf("NO\n");
            continue;
        }
        bool flag = true;
        for(int i = 0; i < size_s; ++i){
            Point p1 = Stack[i];
            Point p2 = Stack[(i + 1) % size_s];
            int cnt_rgt = 0;
            for(int t = 0; t < N; t++){
                if((Sign(Cross(p2-p1, point[t]-p1), 0.0) == 0) && (Sign((point[t]-p1)*(point[t]-p2), 0.0) <= 0))
                    ++cnt_rgt;
            }
            if(cnt_rgt < 3){
                flag = false;
                break;
            }
        }
        cout<<(flag?"YES":"NO")<<endl;
        //init
    }
    return 0;
}
