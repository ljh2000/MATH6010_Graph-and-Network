# MATH6010_Graph-and-Network
* This is homework for the course MATH6010: Graph and Network (2021-2022 Spring, SJTU).

## Contents
### Lab 1 : Minimun Dominating Set
  Randomly generate graphs that satisfy class theorem conditions and design a greedy algorithm to solve the minimum dominating set problem.

#### Usage
```
❯ g++ Graph_generator.cpp -o Graph_generator.exe
❯ g++ Minimun_Dominating_Set.cpp -o Minimun_Dominating_Set.exe
❯ g++ Test.cpp -o Test.exe
❯ .\Test.exe
```

### Lab 2 : Edge Coloring
  Use conditional probability method to achieve edge dyeing so that the number of K4 in the same color is less than or equal to the expected value.  

#### Usage
```
❯ g++ Edge_Coloring.cpp -o Edge_Coloring
❯ ./Edge_Coloring
```


### Lab 3
#### Uniform graph partition
A complete graph has $2n$ edges，the cost function is defined as:  $E \rightarrow Z^+  \cup \{0\}$

Find uniform graph partition，minimize  $c([X_0, X_1]) = \sum\limits_{\{u, v\} \in E, u \in X_0,  v \in X_1} cos t(u, v)$ 
```
❯ ./test.sh
```

#### Knapsack
There are $N$ items, the value of the first $I $item is $P_i$ and the weight is $W_i$.  The backpack is $B$.

Calculate the maximum value of items that can fit into a backpack if the total weight does not exceed the backpack capacity  

#### Steiner Triple Systems
At a given point set $V$, meet $|V| = v $, $V \equiv 1, 3 \(mod \6)$, meet the requirements of the system is constructed $STS (V, B)$. 
```
❯ g++ SteinerTripleSystems.cpp -o SteinerTripleSystems
❯ ./Edge_Coloring [node_num]
```
