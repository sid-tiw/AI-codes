import numpy as np
import random
from itertools import combinations
from queue import PriorityQueue


# F F F F F F
def main():
    #   taking the input!
    #   Note: for a K-SAT problem to be generated, k <= n(number of variables)
    #   m= number of clause
    print("Number of clauses: ")
    m = int(input())
    print("Number of variables: ")
    n = int(input())
    print("Number of litrals in each clause, it should be less than",n)
    k = int(input())
    clauses = generate_clauses(m,n,k)
    print(clauses)
    init_config=[]
    for _ in range(n):
        init_config.append(False)
    print(init_config)
    final_config = hill_climbing(clauses,init_config,n,m,0)#beam_search(clauses,init_config,3)#$hill_climbing(clauses,init_config,n,m)
    print("--------------------------------------------------------------------------------------------------------")
    print("Final configuration after performing hill climbing is",final_config[0])
    print("penetrance for hill climbing P_hillclimbilg= ",1)  

    beam_config = beam_search(clauses,init_config,3)
    print("Final confing after performing beam search is",beam_config[1])
    print("Penetrence for beamsearch with width = 3 is => ",1/3)

    beam_config4 = beam_search(clauses,init_config,4)
    print("Final confing after performing beam search is",beam_config4[1])
    print("Penetrence for beamsearch with width = 4 is => ",1/4)
    print("--------------------------------------------------------------------------------------------------------")



# generating 'm' number of clause such that each clause
# has k litrals, i.e. a distinct variables or their negation 
# not both!!!

def generate_clauses(m,n,k): #clauses,variables,litrals
    clauses=[]
    # variables and their negation are represented as +/- integers
    
    while(len(clauses)!=m):
        clause=[]
        clause.clear()
        while(len(clause)!=k):
            r_litral = int(random.randint(-n,n)) # -5,5
            if r_litral not in clause and (-1*r_litral not in clause) and (r_litral!=0):
                clause.append(r_litral)
        if(clause not in clauses): 
            clauses.append(clause)
    return clauses

# arguments = clauses, variable configuration
# returns the number of clause whose value is true
def heuristic(clauses, var_config):
    hcost=0
    for i in range(len(clauses)):
        true_val=False
        for j in range(len(clauses[i])):
            # print(clauses[i][j])
            if clauses[i][j]<0:
                true_val|=(not(var_config[int(abs(clauses[i][j]))-1]))
            else:
                true_val|= (var_config[int(clauses[i][j])-1])
            
        if true_val:
            hcost+=1
    return hcost


# a,b,c,d => (a,b) (-a,c) (-b,d) ftff
def hill_climbing(clauses, var_config,n,m,path):
    cost = heuristic(clauses,var_config)
    # print(cost)
    if(cost == m):
        return var_config,path
    else:
        optimum_state=var_config
        for i in range(n):
            var_config[i]=not(var_config[i])
            state_cost = heuristic(clauses,var_config)
            if state_cost > cost:
                optimum_state=var_config.copy()
                cost=state_cost
            var_config[i]=not(var_config[i])
        # print(optimum_state)
        if optimum_state == var_config:
            return optimum_state,path
        return hill_climbing(clauses,optimum_state,n,m,path+1)
            
def beam_search(clauses, var_config,width):
    frontier = []
    frontier.append((0,var_config))
    curr_config = (0,var_config)
    vis=[]
    while len(frontier)!=0:
        fl=0
        curr_config = frontier[0]
        # visited.append(curr_config)
        frontier.pop(0)
        for i in range(len(vis)):
            if curr_config == vis[i]:
                fl=1
        if(fl):
            continue
        vis.append(curr_config)
        state_cost = len(clauses) - heuristic(clauses,curr_config[1])
        if(state_cost==0):
            return curr_config
        for i in range(len(curr_config[1])):
            curr_config[1][i]=not(curr_config[1][i])
            new_config = curr_config[1].copy()
            state_cost = len(clauses) - heuristic(clauses,curr_config[1])
            frontier.append((state_cost,new_config))        
            curr_config[1][i]=not(curr_config[1][i])
        frontier.sort(key = lambda x: x[0])
        lgt = len(frontier)
        if width < lgt:
            del frontier[width:lgt]
    return curr_config


if __name__=="__main__":
    main()