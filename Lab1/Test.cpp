#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <complex>
#include <bitset>
using namespace std;
typedef long long LL;
typedef long double LB;
typedef complex<double> C;
const double pi = acos(-1);
 
int main()
{
    int Case_num;
    Case_num = 100;

    int t = 0;
    while( ++t <= Case_num) {
        printf("Test %d : ",t);
        system("Graph_generator.exe");
        system("Minimun_Dominating_Set.exe");
        //if(system("fc 1.out 2.out")){ printf("WA\n"); break;  }
        //else printf("AC\n");

        cout << endl;
    }
    return 0;
}