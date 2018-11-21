/*
  http://bailian.openjudge.cn/practice/1182/
  4824KB
  184ms
  食物链，需要处理好四条边之间的关系就好了，可以选择用向量做，但是没想好QAQ
*/
#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 50005;
int Root[MAXN];
int Relation[MAXN];
int N,K,D,X,Y;
void Init(){
    for(int i = 1; i <= N; i++){
        Root[i] = i;
        Relation[i] = 0;
    }
}

int FndRoot(int i){
    if(Root[i] == i) return i;
    int org_root = Root[i];
    int new_root = FndRoot(org_root);
    Relation[i] = (Relation[i] + Relation[org_root]) % 3;
    Root[i] = new_root;
    return new_root;
}

int main()
{
    scanf("%d %d",&N,&K);
    Init();
    int cnt_lie = 0;
    for(int i = 0; i < K; i++) {
        scanf("%d %d %d", &D, &X, &Y);
        if (X > N || Y > N){
            ++cnt_lie;
            continue;
        }
        if(D == 1){
            int r1 = FndRoot(X), r2 = FndRoot(Y);
            if(r1 != r2){
                Root[r1] = r2;
                Relation[r1] = (Relation[Y]-Relation[X]+3) % 3;
                continue;
            }
            else{
                if(Relation[X] != Relation[Y]){
                    ++cnt_lie;
                    continue;
                }
            }
        }
        else if(D == 2){
            if(X == Y){
                ++cnt_lie;
                continue;
            }
            int r1 = FndRoot(X), r2 = FndRoot(Y);
            if(r1 != r2){
                Root[r1] = r2;
                Relation[r1]=(4+Relation[Y]-Relation[X])%3;
            }
            else{
                if((4 - Relation[Y] + Relation[X])%3 != 2){
                    ++cnt_lie;
                    continue;
                }
            }
        }
    }
    printf("%d\n",cnt_lie);
    return 0;
}
