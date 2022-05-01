#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;


vector<vector<int>> valueTable;
vector<int> SolutionSetU;
vector<int> SolutionSetV;
int n;

int randomInt(int a, int b);
void printValueTable();
void initValue(int n);
void solveUniformGraphPartition();
int calculateSum(int element, vector<int> Set);
bool checkMin();
bool needExchange(int a,int b);
void printSolution();
void Exchange(int i, int j);
int sum();


void Exchange(int i, int j){
    int tmpValue = SolutionSetU[i];
    SolutionSetU[i] = SolutionSetV[j];
    SolutionSetV[j] = tmpValue;
}

int randomInt(int a, int b){
    return (rand() % (b-a))+ a;
}

void printValueTable(){
    cout<<"n = "<< n <<", Value Table: "<<endl;
    int n2 = 2 * n;
    for(int i = 0 ; i < n2; i++){
        for(int j =0 ; j < n2; j++ ){
            cout << valueTable[i][j]<<'\t';
        }
        cout << endl;
    }
}


void initValue(int n){

    // resize Value Table
    valueTable.resize(2 * n);
    for(int i = 0; i < 2* n; i++ ){
        valueTable[i].resize(2*n);
    }
    // init ValueTable
    for(int i = 0; i < 2 * n; i++){
        valueTable[i][i] = 0;
        for(int j = i + 1; j < 2 * n; j++ ){
            valueTable[i][j] = randomInt(1,10);
            valueTable[j][i] = valueTable[i][j];
        }
    }
    // resize solution
    SolutionSetU.resize(n);
    SolutionSetV.resize(n);

    // init Solution
    for (int i = 0; i < n; i++){
        SolutionSetU[i] = i;
        SolutionSetV[i] = i + n;
    }
}


int calculateSum(int element, vector<int> Set){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += valueTable[element][Set[i]];
    }
    return sum;
}




void solveUniformGraphPartition(){
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (needExchange(i,j)){
                Exchange(i,j);
            }
        }
    }
}


bool needExchange(int a,int b){
    int now = calculateSum(SolutionSetU[a],SolutionSetV) + calculateSum(SolutionSetV[b],SolutionSetU) - valueTable[SolutionSetU[a]][SolutionSetV[b]] * 2;
    int after = calculateSum(SolutionSetU[a],SolutionSetU) + calculateSum(SolutionSetV[b],SolutionSetV);
    return after < now;
}


int sum(){
    int sum = 0;
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n;j++){
            sum += valueTable[SolutionSetU[i]][SolutionSetV[j]];
        }
    }
    return sum;
}

bool checkMin(){
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (needExchange(i,j)){
                // cout<<"Not min, exchange "<<SolutionSetU[i]<<" and "<<SolutionSetV[j]<<endl;
                // cout<<"before "<<sum()<<endl;
                // Exchange(i,j);
                // cout<<"after "<<sum()<<endl;
                return false;
            }
        }
    }
    // cout <<"MIN !"<<endl;
    return true;
}





void printSolution(){
    cout<<"solution set U: "<<endl;
    for(int i = 0; i < n; i++){
        cout << SolutionSetU[i]<<'\t';
    }
    cout<<endl<<"solution set V: "<<endl;
    for(int i = 0; i < n; i++){
        cout << SolutionSetV[i]<<'\t';
    }
    cout<<endl;
    cout << "Min CIJ : "<<sum()<<endl;
    // cout<<"Is Min?"<<endl;
    // checkMin();
    // cout<<checkMin()<<endl;
}

int main(int argc, char** argv){
    srand(time(0));

    if (argc == 1)
        n = 10;
    else
        n = stoi(argv[1]);

    initValue(n);
    printValueTable();

    while(!checkMin()){
        solveUniformGraphPartition();
    }

    printSolution();
    cout << endl ;

    return 0;
}