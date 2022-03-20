#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <set>
#include <queue>

using namespace std;
const int maxn = 100;
const int maxm = 1000;
int n,m,ecnt;
bool in_set[maxn]; // in dominating set
bool cont[maxn]; // under control
int sz;
int first[maxn];
int rk[maxn]; // rank

set<int>doms;

struct edge{
    int to;
    int nxt;
}e[maxm];

void add_edge(int x,int y){
    e[++ecnt].nxt = first[x];
    e[ecnt].to = y; 
    first[x] = ecnt;

    e[++ecnt].nxt = first[y];
    e[ecnt].to = x; 
    first[y] = ecnt;
}

bool solve(){
    memset(cont,0,sizeof(cont));
    memset(rk,0,sizeof(rk));

    // initialize
    set<int>::iterator it = doms.begin();
    while (it != doms.end()){
        //cout << *it << " ";
        int x = (*it);
        
        cont[x] = 1;
        for(int i = first[x] ; i ; i = e[i].nxt)
            cont[ e[i].to ] = 1;

        it++;
    }

    // check
    int dom_sz = 0;
    for(int x = 1;x <= n;x++)
        if(cont[x]) 
            dom_sz++;     
    if(dom_sz == n) return true;

    // caculate ranks
    for(int x = 1;x <= n;x++){
        if(cont[x]) continue;
        for(int i = first[x] ; i ; i = e[i].nxt) {
            if(in_set[ e[i].to ]) continue;
            rk[ e[i].to ] ++;
        }
    }

    // greedy algorithm
    int maxrk = -1, flag = 1;
    for(int x = 1;x <= n;x++) {
        if(rk[x] > maxrk) {
            maxrk = rk[x];
            flag = x;
        }
    }

    doms.insert(flag);
    in_set[flag] = 1;
    sz ++;

    //cout << sz << " : " << flag << endl;
    return false;
}

int main()
{
    freopen("Graph.in","r",stdin);
    freopen("Graph.out","w",stdout);
    
    cin >> n >> m;
    for(int i = 1;i <= m;i++) {
        int x,y;
        cin >> x >> y;
        add_edge(x,y);
    }
    
    while(!solve()) ;

    cout << "dominating set size : " << sz << endl;
    set<int>::iterator it = doms.begin();
    while (it != doms.end()){
        cout << (*it) << " ";
        it++;
    }

    return 0;
}
