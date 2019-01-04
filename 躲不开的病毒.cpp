/*
  http://dapractise.openjudge.cn/2018hwall/012/
  1000kB
  98ms
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <deque>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
char virus[30005];
struct Node{
    Node* pChild[2];
    bool bBadNode;
    bool bVisitedNode;
    Node* pPrev;
    Node(){
        pPrev = NULL;
        memset(pChild, 0, sizeof(pChild));
        bVisitedNode = bBadNode = false;
    }
}Tree[30005];
int nNodeCount = 2;
int N;
void Insert()
{
    Node* pRoot = Tree + 1;
    int len_v = strlen(virus);
    for(int i = 0; i < len_v; ++i){
        if(pRoot->pChild[virus[i]-'0'] == NULL){
            pRoot->pChild[virus[i]-'0'] = Tree + nNodeCount;
            nNodeCount++;
        }
        pRoot = pRoot->pChild[virus[i]-'0'];
    }
    pRoot->bBadNode = true;
}
void Build()
{
    Node* pRoot = Tree + 1;
    for(int i = 0; i < 2; ++i){
        Tree[0].pChild[i] = Tree + 1;
    }
    Tree[0].pPrev = NULL;
    Tree[1].pPrev = Tree;
    deque<Node*> dq;
    dq.push_back(pRoot);
    while(!dq.empty()){
        Node* pTop = dq.front();
        dq.pop_front();
        for(int i = 0; i < 2; ++i){
            Node* p = pTop->pChild[i];
            if(p){
                Node* pPrev = pTop->pPrev;
                while(pPrev->pChild[i] == NULL){
                    pPrev = pPrev->pPrev;
                }
                p->pPrev = pPrev->pChild[i];
                if(p->pPrev->bBadNode){
                    p->bBadNode = true;
                }
                dq.push_back(p);
            }
        }
    }

}
bool flag = false;
void Search(Node* pRoot)
{
    if(flag){
        return;
    }
    if(pRoot->bBadNode){
        return;
    }
    if(pRoot->bVisitedNode){
        flag = true;
        return;
    }
    pRoot->bVisitedNode = true;
    for(int i = 0; i < 2; ++i){
        if(pRoot->pChild[i]){
            Search(pRoot->pChild[i]);
        }
        else{
            Node* pPrev = pRoot->pPrev;
            while(pPrev->pChild[i] == NULL){
                pPrev = pPrev->pPrev;
            }
            Search(pPrev->pChild[i]);
        }
    }
    pRoot->bVisitedNode = false;
}
int main()
{
    scanf("%d", &N);
    while(N--){
        cin>>virus;
        Insert();
    }
    Build();
    Search(Tree + 1);
    cout<<(flag?"TAK":"NIE")<<endl;
    return 0;
}
