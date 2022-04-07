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
const int maxn = 200+12;
const int maxm = 40000+12;

int n,m;
int id[maxm];
int col[maxn][maxn];
double pow2[12];
double ans , avg_ans;

struct edge{
    int x,y;
}e[maxm];

void init_edge(){
    srand(time(NULL));

    int ecnt = 0;
    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++) {
            ecnt ++;
            e[ecnt].x = i;
            e[ecnt].y = j;
        }

    for(int i = 1; i <= m; i++) id[i] = i;
    random_shuffle(id+1,id+m+1);
    //for(int i = 1; i <= m; i++) cout << id[i] << endl;
}

// black:1  white:2  null:0
double calc_Ik4(int col1, int col2, int col3, int col4, int col5, int col6){
    int k4_col = col1 | col2 | col3 | col4 | col5 | col6;
    int r = (col1>0) + (col2>0) + (col3>0) + (col4>0) + (col5>0) + (col6>0);

    // black and white : 0
    if(k4_col == 3) return 0;

    // null : 2^(-5)
    if(r == 0) return pow2[5];

    // black or white : 2^(r-6)
    return pow2[6-r];    
}

void color_edge(){
    ans = avg_ans;

    for(int idx = 1; idx <= m; idx++) {
        int x = e[ id[idx] ].x;
        int y = e[ id[idx] ].y;

        // calculate W_black and W_white
        double W_black = ans , W_white = ans;

        for(int i = 1; i <= n; i++) {
            if(x == i || y == i) continue;
            for(int j = i+1 ; j <= n;j++) {
                if(x == j || y == j) continue;

                // K4: x y i j
                double current_Ik4 = calc_Ik4(col[x][y], col[x][i], col[x][j], col[y][i], col[y][j], col[i][j]);

                W_black -= current_Ik4;
                W_black += calc_Ik4(1, col[x][i], col[x][j], col[y][i], col[y][j], col[i][j]);

                W_white -= current_Ik4;
                W_white += calc_Ik4(2, col[x][i], col[x][j], col[y][i], col[y][j], col[i][j]);

            }
        }

        //cout << W_black << " " << W_white << endl;

        if(W_black <= W_white) {
            ans = W_black;
            col[x][y] = col[y][x] = 1;
        }
        else {
            ans = W_white;
            col[x][y] = col[y][x] = 2;
        }
    }
}

int main()
{
    //n = 200;
    //n = 6;
    n = 150;
    m = n*(n-1)/2;

    // preprocess powers of two
    pow2[0] = 1;
    for(int i = 1;i <= 6; i++) pow2[i] = pow2[i-1] / 2.0;
    //for(int i = 1;i <= 6; i++) cout << pow2[i] << " " ;

    init_edge();

    avg_ans = n * (n-1) * (n-2) * (n-3) / 24;
    avg_ans *= pow2[5];
    cout << "Expected number of K4 in the same color : " << avg_ans << endl;

    color_edge();

    cout << "Final answer : " << ans << endl;

    /*for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) 
            cout << col[i][j] << " ";
        cout << endl;
    }*/

    return 0;
}
