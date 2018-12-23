/*
  课件模板题，有点东西quq

*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
#include <cstdio>
using namespace std;
double y[210];
struct CNode{
    int L, R;
    CNode* pLeft, * pRight;
    double Len;//本区间当前是有多长的部分是落在那些矩形里面的
    int Covers;//本区间当前被多少个节点完全覆盖
}Tree[1005];
struct CLine{
    double x, y1, y2;
    bool bLeft;
}lines[210];
int nNodeCount = 0;
bool operator < (const CLine& l1, const CLine& l2){
    return l1.x < l2.x;
}

template <class F, class T>
F bin_search(F s, F e, T val)
{
    F L = s;
    F R = e - 1;
    while(L <= R){
        F mid = L + (R - L) / 2;
        if(!(*mid < val || val < *mid))
            return mid;
        else if(val < *mid){
            R = mid - 1;
        }
        else{
            L = mid + 1;
        }
    }
    return e;
}

int Mid(CNode* pRoot)
{
    return (pRoot->L + pRoot->R) / 2;
}
void Insert(CNode* pRoot, int L, int R){
    if(pRoot->L == L && pRoot->R == R){
        pRoot->Len = y[R + 1] - y[L];
        pRoot->Covers ++;
        return;
    }
    int midRoot = Mid(pRoot);
    if(R <= midRoot){
        Insert(pRoot->pLeft, L, R);
    }
    else if(L > midRoot){
        Insert(pRoot->pRight, L, R);
    }
    else{
        Insert(pRoot->pLeft, L, midRoot);
        Insert(pRoot->pRight, midRoot + 1, R);
    }
    if(pRoot->Covers == 0){
        pRoot->Len = pRoot->pLeft->Len + pRoot->pRight->Len;
        //不为0，说明本区间仍然被矩形完全覆盖，则不能更新len;
    }
}
void Delete(CNode* pRoot, int L, int R){
    if(pRoot->L == L && pRoot->R == R){
        pRoot->Covers --;
        if(pRoot->Covers == 0){
            if(pRoot->L == pRoot->R){
                pRoot->Len = 0;
            }
            else{
                pRoot->Len = pRoot->pLeft->Len + pRoot->pRight->Len;
            }
        }
        return;
    }
    int midRoot = Mid(pRoot);
    if(R <= midRoot){
        Delete(pRoot->pLeft, L, R);
    }
    else if(L > midRoot){
        Delete(pRoot->pRight, L, R);
    }
    else{
        Delete(pRoot->pLeft, L, midRoot);
        Delete(pRoot->pRight, midRoot + 1, R);
    }
    if(pRoot->Covers == 0){
        pRoot->Len = pRoot->pLeft->Len + pRoot->pRight->Len;
    }
}
void BuildTree(CNode* pRoot, int L, int R)
{
    pRoot->L = L;
    pRoot->R = R;
    pRoot->Covers = 0;
    pRoot->Len = 0;
    if(L == R){
        return;
    }
    nNodeCount++;
    pRoot->pLeft = Tree + nNodeCount;
    nNodeCount++;
    pRoot->pRight = Tree + nNodeCount;
    BuildTree(pRoot->pLeft, L, (L + R) / 2);
    BuildTree(pRoot->pRight, (L + R) / 2 + 1, R);
}
int main()
{
    int n = 0;
    int i = 0, j = 0, k = 0;
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    int yc = 0, lc = 0;
    int nCount = 0;
    int t = 0;//t is the number of case
    while(true){
        scanf("%d", &n);
        if(!n) break;
        t++;
        yc = lc = 0;
        for(int i = 0; i < n; i++){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            y[yc++] = y1;
            y[yc++] = y2;
            lines[lc].x = x1;
            lines[lc].y1 = y1;
            lines[lc].y2 = y2;
            lines[lc].bLeft = true;
            lc ++;
            lines[lc].x = x2;
            lines[lc].y1 = y1;
            lines[lc].y2 = y2;
            lines[lc].bLeft = false;
            lc ++;
        }
        sort(y, y + yc);
        yc = unique(y, y + yc) - y;

        nNodeCount = 0;
        BuildTree(Tree, 0, yc - 1 - 1);
        sort(lines, lines + lc);
        double Area = 0.0;
        for(int i =  0; i < lc - 1; i++){
            int L = bin_search(y, y + yc, lines[i].y1) - y;
            int R = bin_search(y, y + yc, lines[i].y2) - y;
            if(lines[i].bLeft){
                Insert(Tree, L, R - 1);
            }
            else{
                Delete(Tree, L, R - 1);
            }
            Area += Tree[0].Len * (lines[i + 1].x - lines[i].x);

        }
        printf("Test case #%d\n", t);
        printf("Total explored area: %.2lf\n", Area);
        printf("\n", Area);

    }
    return 0;
}
