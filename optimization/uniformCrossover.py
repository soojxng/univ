"""
Generate an offspring by Implementing tournament selection and uniform crossover for one-max problem.
-Generate a population with 30 binary arrays randomly.
-The length of the chromosome is 10.
-The fitness of each chromosome is the number of 1's.
"""

import random

def tournamentSelect(li):
    li2 = random.sample(li, 4)
    s_list = []
    for i in range(2):
        if li2[i*2][1] > li2[i*2+1][1]:
            s_list.append(li2[i*2])
        else:
            s_list.append(li2[i*2+1])
    return s_list
    
def makeChromosomes():
    li = []
    for _ in range(30):
        x = ""
        for __ in range(10):
            x += str(random.randrange(0,2))   
        li.append([x, x.count("1")])
    return li

def printChromosomes(li):
    for i in range(30):
        print(f'{i}: {li[i][0]} (f: {li[i][1]})')
        
def uniformCrossover(s1, s2):
    offspring = ""
    for i in range(10):
        r = round(random.random(), 2)
        if(r >= 0.5):
            offspring += s1[0][i]
        else:
            offspring += s2[0][i]
    return offspring
    

print("- Generated population")
li = makeChromosomes()
printChromosomes(li)
    
print("- Tournament selection")
s1, s2 = tournamentSelect(li)
print(f'Parent 1: {s1[0]} (f: {s1[1]})')
print(f'Parent 2: {s2[0]} (f: {s2[1]})')

print("- Uniform crossover")
offspring = uniformCrossover(s1, s2)
print(f'Offspring: {offspring} (f: {offspring.count("1")})')
