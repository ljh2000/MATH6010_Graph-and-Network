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
#include <map>
using namespace std;
const int maxv = 200;
const int maxb = 200000;
int v , NumBlocks;
int bel[maxv][maxv]; // pair belongs to triple
int triple_cnt; // the number of triples
int deg[maxv]; // the degree of node
int live_points[maxv]; // live points list

struct triple{
    int x,y,z;
    bool in;
} Block[maxb];

// SWITCH operation
void Switch_op(){
    int tot = 0;
    for(int i = 1;i <= v; i++) 
        if(deg[i] < (v-1)/2)
            live_points[ ++tot ] = i;

    random_shuffle(live_points+1,live_points+tot+1);

    int x = live_points[1];

    int y,z;
    // find y
    for(int i = 1;i <= v;i++) {
        if(i == x) continue;
        if(bel[x][i]) continue;
        y = i; 
        break;
    }    

    // find z
    for(int i = y+1; i <= v;i++) {
        if(i == x) continue;
        if(bel[x][i]) continue;
        z = i;
        break;
    }

    triple_cnt++;
    Block[triple_cnt].x = x;
    Block[triple_cnt].y = y;
    Block[triple_cnt].z = z;
    Block[triple_cnt].in = true;

    // case 1:
    if(bel[y][z] == 0) {
        deg[y] ++;
        deg[z] ++;
        NumBlocks++;
    }
    // case 2:
    else {
        int old_triple = bel[y][z];
        int w;
        
        if(Block[old_triple].y == y && Block[old_triple].z == z) w = Block[old_triple].x;
        if(Block[old_triple].y == z && Block[old_triple].z == y) w = Block[old_triple].x;
        if(Block[old_triple].x == y && Block[old_triple].z == z) w = Block[old_triple].y;
        if(Block[old_triple].x == z && Block[old_triple].z == y) w = Block[old_triple].y;
        if(Block[old_triple].x == y && Block[old_triple].y == z) w = Block[old_triple].z;
        if(Block[old_triple].x == z && Block[old_triple].y == y) w = Block[old_triple].z;

        
        Block[old_triple].in = false;
        bel[w][y] = bel[w][z] = bel[y][w] = bel[z][w] = 0;
        
        deg[w] --;
    }

    deg[x] ++;
    bel[x][y] = bel[y][x] = bel[y][z] = bel[z][y] = bel[x][z] = bel[z][x] = triple_cnt;

    //printf("triple %d : %d %d %d\n Block_num = %d\n",triple_cnt,x,y,z,NumBlocks);
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    if (argc == 1)
        v = 7;
    else
        v = atoi(argv[1]);

    while(NumBlocks < v*(v-1)/6)
        Switch_op();

    printf("STS(%d):\n",v);
    printf("V={");
    for(int i = 1;i <= v;i++) {
        if(i != 1) printf(",");
        printf("%d",i);
    }
    printf("}\n");

    printf("B={");
    int sort_block[3];
    for(int i = 1;i <= triple_cnt;i++) {
        if(!Block[i].in) continue;
        sort_block[0] = Block[i].x;
        sort_block[1] = Block[i].y;
        sort_block[2] = Block[i].z;
        sort(sort_block,sort_block+3);
        printf("{%d %d %d}",sort_block[0],sort_block[1],sort_block[2]);
        if(i != triple_cnt) printf("\n");
    }
    printf("}\n\n");
    return 0;
}
