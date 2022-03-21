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
#include <ctime>

using namespace std;

const int maxn = 100;
const int maxm = 10000;
int n,m,fa[maxn];
bool graph[maxn][maxn];

struct edge{
    int x,y;
}e[maxm];

int find(int x){
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

bool check(){
    memset(graph,0,sizeof(graph));
    int mcnt = 0;
    while(mcnt < m) {
        int x,y;
        x = rand() % n + 1;
        y = rand() % n + 1;
        if(x > y) swap(x,y);

        if(x == y || graph[x][y]) continue;

        graph[x][y] = 1;
        mcnt ++;
        //cout << x << " " << y << endl;
        e[mcnt].x = x; e[mcnt].y = y;
    }

    for(int i = 1;i <= n;i++) fa[i] = i;
    for(int i = 1;i <= m;i++){
        int fx,fy;
        fx = find(e[i].x);
        fy = find(e[i].y);
        if(fx != fy)
            fa[fx] = fy;
    }

    for(int i = 2;i <= n;i++) 
        if(find(i) != find(1))
            return false;
    return true;
}

int main()
{
    freopen("Graph.in","w",stdout);
    //n = 8;
    //m = 10;

    n = 10;
    m = 19;

    cout << n << " " << m << endl;

    srand(time(NULL));

    while(!check()) ;

    for(int i = 1;i <= m;i++) 
        cout << e[i].x << " " << e[i].y << endl;

    return 0;
}