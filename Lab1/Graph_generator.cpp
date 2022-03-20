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

const int maxn = 1000;
int n,m;
bool graph[maxn][maxn];

int main()
{
    freopen("Graph.in","w",stdout);
    n = 8;
    m = 18;
    cout << n << " " << m << endl;

    srand(time(NULL));

    int mcnt = 0;
    while(mcnt < m) {
        int x,y;
        x = rand() % n + 1;
        y = rand() % n + 1;
        if(x > y) swap(x,y);

        if(x == y || graph[x][y]) continue;

        graph[x][y] = 1;
        mcnt ++;
        cout << x << " " << y << endl;
    }
    
    return 0;
}