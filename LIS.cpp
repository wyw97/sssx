/*
  http://dapractise.openjudge.cn/2018hwall/005/
  13912 kB
  610ms
  nlogn时间求最长上升子序列，
  通过对原数组进行排序，按照从小到大的顺序依次访问，如果元素相同，则在后出现的元素
  先进行操作。轮到某个节点时，该位置的Count函数应该为原来的max + 1，然后更新包含
  这一项的全部count数组。count数组可以理解为包含[i-lowbit(i)+1,i]以该区间中元
  素为结尾的最长LIS，然后向后update即可。
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct Info{
    int num;
    int loc;//recore the location;
}info[300005];
int Count[300005];
int N;
int cmp(Info i1,Info i2){
    return i1.num < i2.num || (i1.num == i2.num && i1.loc > i2.loc);
}
int lowbit(int x){
    return x & (-x);
}
void Update(int i, int num){
    while(i <= N){
        Count[i] = max(num, Count[i]);
        i += lowbit(i);
    }

}
int Query(int i)
{
    int maxn = Count[i];
    while(i > 0){
        maxn = max(maxn, Count[i]);
        i -= lowbit(i);
    }
    return maxn;
}
int main()
{
    scanf("%d",&N);
    for(int i = 1; i <= N; i++){
        scanf("%d",&info[i].num);
        info[i].loc = i;
    }
    sort(info + 1, info + N + 1, cmp);
    int max_count = 0;
    for(int i = 1; i <= N; i++){
        int tmp_loc = info[i].loc;
        Count[tmp_loc] = Query(tmp_loc) + 1;
        Update(tmp_loc, Count[tmp_loc]);
    }
    for(int i = 1; i <= N; i++){
        max_count = max(max_count, Count[i]);
    }
    printf("%d\n",max_count);
}
