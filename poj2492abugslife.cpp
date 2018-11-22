/*
  http://bailian.openjudge.cn/practice/2492/
  11904kb
  400ms
  简单的二类关系寻根即可。
  还是不会向量化qaq
*/
#include <iostream>
#include <cstdio>
using namespace std;
int Cases = 0;
int Bugs = 0, Interactions = 0;
const int MAXN = 2005;
int Root[MAXN];
int Relation[MAXN];
void Init()
{
    for(int i = 1; i <= Bugs; i++){
        Root[i] = i;
        Relation[i] = 0;
    }
}
int FndRoot(int i)
{
    if(i == Root[i]) return i;
    int org_root = Root[i];
    Root[i] = FndRoot(org_root);
    Relation[i] = (Relation[i] + Relation[org_root]) % 2;
    return Root[i];
}
int main()
{
    scanf("%d",&Cases);
    for(int i = 1; i <= Cases; i++){

        scanf("%d %d",&Bugs,&Interactions);
        Init();
        bool flag = false;
        int bug1, bug2;
        for(int i = 0; i < Interactions; i++){
            scanf("%d %d",&bug1,&bug2);
            if(flag) continue;
            int r1 = FndRoot(bug1), r2 = FndRoot(bug2);
            if(r1 != r2){
               Root[r1] = r2;
               Relation[r1] = (Relation[bug1] + Relation[bug2] + 1) % 2;
            }
            else{
                if(Relation[bug1] == Relation[bug2]){
                    flag = true;
                }
            }

        }
        printf("Scenario #%d:\n",i);
        if(flag){
            printf("Suspicious bugs found!\n\n");
        }
        else{
            printf("No suspicious bugs found!\n\n");
        }
    }
    return 0;
}
