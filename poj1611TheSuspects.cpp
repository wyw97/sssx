/*
  http://bailian.openjudge.cn/practice/1611/
  648KB 
  14ms
  并查集基础题，同一个团体的人把第一个的根节点当成根节点即可。
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdio>
using namespace std;
int N,M;
int Cnt[30005];//记录每个节点的根节点的个数;
int Father[30005];//找父亲;
void Init()
{
    for(int i=0;i<N;i++){
        Father[i] = i;
        Cnt[i] = 1;
    }
}
int Fndfather(int a){
    if(Father[a]!=a){
        Father[a]=Fndfather(Father[a]);
    }
    return Father[a];
}
int main() {
    while(scanf("%d %d",&N,&M)){

        if(!N && !M) break;
        Init();
        int cnt_temp = 0, fst_num = 0;
        for(int i=0;i<M;i++){
            scanf("%d %d",&cnt_temp,&fst_num);
            //cin>>cnt_temp;cin>>fst_num;
            int temp_father = Fndfather(fst_num);
            int temp_point = 0;
            for(int j=1; j<cnt_temp; j++){
                scanf("%d",&temp_point);
                int temp_father2 = Fndfather(temp_point);
                if(temp_father != temp_father2){
                    Father[temp_father2] = temp_father;
                    Cnt[temp_father] += Cnt[temp_father2];
                }
            }
        }
        printf("%d\n",Cnt[Fndfather(0)]);
    }
    return 0;
}
