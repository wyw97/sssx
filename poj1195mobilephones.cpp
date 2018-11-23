/*
  http://bailian.openjudge.cn/practice/1195/
  8084 KB
  238 ms
  二维树状数组，可以说是模板题了。
*/
#include <iostream>
#include <cstdio>
using namespace std;
int S[1030][1030];
int Cnt[1030][1030];
int lowbit(int x){
    return x & (-x);
}
int s;
int t_cmd, a1, a2, a3, a4;
void Update(int x,int y,int num){
    for(int i = x; i <= s; i += lowbit(i)){
        for(int t = y; t <= s; t += lowbit(t)){
            Cnt[i][t] += num;
        }
    }
}
long long int Add(int x, int y)
{
    long long int sumn = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        for(int j = y; j > 0; j -= lowbit(j)){
            sumn += Cnt[i][j];
        }
    }
    return sumn;
}
int main()
{
    while(scanf("%d",&t_cmd)){
        if(t_cmd == 3) break;
        else if(t_cmd == 0){
            scanf("%d",&s);
        }
        else if(t_cmd == 1){
            scanf("%d %d %d", &a1, &a2, &a3);
            Update(a1 + 1, a2 + 1, a3);
        }
        else if(t_cmd == 2){
            scanf("%d %d %d %d", &a1, &a2, &a3, &a4);
            long long int res = Add(a3 + 1, a4 + 1) + Add(a1, a2) - Add(a1, a4 + 1) - Add(a3 + 1, a2);
            printf("%lld\n",res);

        }
    }
    return 0;
}
