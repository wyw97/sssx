/*
  http://bailian.openjudge.cn/practice/1988/
  3000 kb
  799ms
  需要使用三个数组，分别记录根节点，根节点所在的堆的全部个数，以及当前块下面的stack数目，
  更新的时候需要注意在合并的时候更新堆个数数组，在寻找父节点的时候更新under数组。
*/
#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 30005;
int P;
int Root[MAXN];
int Cnt[MAXN];
int Under[MAXN];
int FndRoot(int i){
    if(Root[i] == i) return i;
    int org_rt = Root[i];
    int new_rt = FndRoot(org_rt);
    Root[i] = new_rt;
    Under[i] += Under[org_rt];
    return new_rt;
}
void Merge(int n1, int n2)
{
    int r1 = FndRoot(n1), r2 = FndRoot(n2);
    if(r1 == r2) return;
    Root[r2] = r1;

    Under[r2] += Cnt[r1];
    Cnt[r1] += Cnt[r2];
}
void Init()
{
    for(int i = 1; i < MAXN; i++){
        Root[i] = i;
        Cnt[i] = 1;
        Under[i] = 0;
    }
}
int main()
{
    scanf("%d",&P);
    Init();
    char cmd;
    int num1 = 0, num2 = 0;
    for(int i = 0; i < P; i++){
        cin>>cmd;
        if(cmd - 'M' == 0){
            scanf("%d %d", &num1, &num2);
            Merge(num2, num1);
        }
        else if(cmd - 'C' == 0){
            scanf("%d", &num1);
            FndRoot(num1);//necessary
            printf("%d\n",Under[num1]);
        }
    }
    return 0;
}
