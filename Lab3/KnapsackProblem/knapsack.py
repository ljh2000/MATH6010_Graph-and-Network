import random
import numpy as np
import itertools
import argparse

def set_seed(seed=1000):
    random.seed(seed)
    np.random.seed(seed)


set_seed()



class Knapsack(object):
    def __init__(self,amount,capacity,max_weight,max_val):
        self.capacity = capacity
        self.amount = amount
        self.value = np.random.randint(1,max_val,self.amount)
        self.weight = np.random.randint(1,max_weight,self.amount)
        print("---------------  Settings  ----------------")
        print(" [Number] {} Items and A Knapsack with [Capacity] {} ".format(amount,capacity))
        print(" [Weight] {}".format(self.weight))
        print(" [Value] {}".format(self.value))
        print("-------------------------------------------")


    # Reasonable Solution
    def take_out(self,sol):
        while 1:
            if sum(sol*self.weight)>self.capacity:
                ind = np.argwhere(sol==1)
                sol[random.choice(ind)] = 0
            else:
                break
        return sol


    # Greedy Algorithm
    def Greedy(self):
        density = -self.value/self.weight
        sorted_ind = np.argsort(density)
        sorted_density = np.sort(density) 
        sorted_cum = np.cumsum(sorted_density)
        greed_cap = self.capacity
        greedy_sol = np.zeros(self.amount)
        for i in range(self.amount):
            if sorted_cum[i]> -greed_cap:
                # print('Put in {}th item [Value] {} [Weight] {}'.format(i,self.value[i],self.weight[i]))
                greed_cap -= self.weight[sorted_ind[i]]
                greedy_sol[sorted_ind[i]] = 1
            else:
                break

        in_bag_v = self.value[sorted_ind[:i]]
        in_bag_w = self.weight[sorted_ind[:i]]
        print(" [ Greddy Value ] : ",sum(in_bag_v))

        print(" [ Greedy Solution ] : ",greedy_sol)


    def init_sol(self,init_val):
        rnd_ind = np.random.permutation(range(self.amount))
        init_sol = np.ones(self.amount)
        np.random.shuffle(rnd_ind)
        init_sol[rnd_ind[:random.choice(rnd_ind)]] = init_val
        init_sol = self.take_out(init_sol)
        return init_sol

    def pert_sol(self,near_sol):
        if np.random.rand()>0.5:
                rnd_ind = np.random.randint(0,self.amount) 
                near_sol[rnd_ind] = abs(near_sol[rnd_ind]-1)
                near_sol = self.take_out(near_sol)
        else:
            rnd_ind = np.random.randint(0,self.amount,2) 
            near_sol[rnd_ind[0]],near_sol[rnd_ind[1]] =near_sol[rnd_ind[1]],near_sol[rnd_ind[0]]
            near_sol = self.take_out(near_sol)
        return near_sol
    # Near Neighbor Solution
    def find_near(self,sol,near_num):
        nears = []
        for _ in itertools.repeat(None, near_num):
            near_sol = self.pert_sol(sol.copy())    
            nears.append(near_sol)
        return np.array(nears)
    # Tabu Search
    def tabu_search(self,tabu_len,epoch,near_num,init_val=0,param_search=False):
        if param_search:
            init_sol = self.fix_init
        init_sol = self.init_sol(init_val)
        init_val = sum(init_sol*self.value)
        vals = [init_val]
        sols = [init_sol]
        tabu_list = []
        best_val = init_val
        best_sol = init_sol.copy()
        
        for i in range(epoch):
            nears = self.find_near(best_sol,near_num)
            near_vals = [sum(-near*self.value) for near in nears]
            val_ind = np.argsort(near_vals)
            for i in val_ind:
                if i not in tabu_list:
      
                    best_sol = nears[i].copy()
                    vals.append(near_vals[i])
                    sols.append(nears[i])
                    tabu_list.append(i)
                    if len(tabu_list) > tabu_len:
                        tabu_list.pop(0)
                    break
                elif near_vals[i]<min(near_vals):
                    tabu_list.remove(i)
                    tabu_list.append(i)
                    vals.append(near_vals[i])
                    sols.append(nears[i])
                    best_sol = nears[i].copy()
          
        
        best_val = sum(best_sol*self.value)
        print(" [ Tabu Search ] : ",best_val)
        return best_val


    #  Dynamic Process
    def DP(self):
        dp = np.zeros(self.capacity+1)
        for i in  range(self.amount):
            for j in range(self.capacity,self.weight[i],-1):
                dp[j] = max(dp[j],dp[j-self.weight[i]]+self.value[i])
        print(" [ Dynamic Programming Value ] : ",dp[self.capacity])

    #  Simulated Anealing
    def simulated_annealing(self,ratio,init_temper,terminal_temper,epoch=100):
        temper = init_temper
        cur_sol = self.init_sol(0)
        new_sol = self.init_sol(1)
        best_val = np.inf
        cur_val = np.inf
        best_sol = np.ones(self.amount)
        it = 0
        anneal_val = -self.value 


        while temper>terminal_temper:
            it+=1
            for i in range(epoch):
                new_sol = self.pert_sol(new_sol.copy())
                new_val = sum(new_sol*anneal_val)
                if new_val<cur_val or np.random.rand()<np.exp(-(new_val-cur_val)/temper):
                    cur_val = new_val
                    cur_sol = new_sol
                else:
                    new_sol = cur_sol
                if cur_val < best_val:
                    best_val = cur_val
                    best_sol = cur_sol.copy() 
            temper *= ratio
        best_val = -best_val
        print(" [ Simulated Annealing Value ] : ",best_val)
        print(" [ Simulated Annealing Solution ] : ",best_sol)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description = "KnapSack Problem")
    parser.add_argument('-capacity',default = 50, type = int)
    parser.add_argument('-amount',default = 10, type = int)
    parser.add_argument('-max_val',default = 100, type = int)
    parser.add_argument('-max_weight',default = 30, type = int)
    parser.add_argument('-cooling_ratio',default = 0.95, type = float)
    parser.add_argument('-init_temper',default = 100, type = int)
    parser.add_argument('-terminal_temper',default = 2, type = int)
    parser.add_argument('-epoch',default = 100, type = int)
    args = parser.parse_args()

    knap = Knapsack(args.amount,args.capacity,args.max_weight,args.max_val)

    knap.Greedy()

    knap.DP()

    knap.simulated_annealing(args.cooling_ratio,args.init_temper,args.terminal_temper,args.epoch)

    # Choose Optimal Param for Tabu Search
    best_val = 0
    knap.fix_init = knap.init_sol(0)
    for epoch in [1000,500,200,100]:
        for near_num in [100,50,20,10,5,3,2,1]:
            for tabu_length in [50,20,10,5,3]:
                print("[epoch]: {},[near_num]:{},[tabu_length]:{}".format(epoch,near_num,tabu_length))
                val = knap.tabu_search(tabu_length,epoch,near_num,param_search = True)
                if val>=best_val:
                    best_val = val
                    best_param = [epoch, near_num, tabu_length]
   #best_param = [1000,100,10]
    print("best_param",best_param)
    knap.tabu_search(*best_param,param_search = True)
