import random

LEN = 20

def makeChromosomes():
    li = []
    for _ in range(30):
        x = ""
        for __ in range(LEN):
           x += str(random.randrange(0,2))
        li.append([x, x.count("1")])
    return li
   
def printChromosomes(li):
    for i in range(30):
       print(f'{i}: {li[i][0]} (f: {li[i][1]})')
       
def tournamentSelect(li):
    li2 = random.sample(li, 4)
    s_list = []
    for i in range(2):
        if li2[i*2][1] > li2[i*2+1][1]:
            s_list.append(li2[i*2])
        else:
            s_list.append(li2[i*2+1])
    return s_list       

def onepointCrossover(p1, p2):
    #random cut point 생성
    cut_point = random.randrange(LEN+1)
    offspring = p1[0][0:cut_point]+p2[0][cut_point:LEN]
    return offspring
        
def bitFlipMutation(li):
    r = round(random.random(), 4)
    if(r <= 0.015):
       i = random.randrange(30)
       j = random.randrange(LEN)
       s = li[i][0][0:j] + ("0" if li[i][0][j] == "1" else "1") + li[i][0][j+1:]
       li[i][0] = s
    return
    
li = makeChromosomes()
cnt = 1
o_list = []
while cnt < 50:
    print("- Generatation", cnt)
    printChromosomes(li)
    m = list(x[1] for x in li)
    maxx = max(m)
    maxi = m.index(maxx)
    print(f'Best: {li[maxi][0]} (f: {li[maxi][1]})')
    
    for _ in range(5):
        #print("- selection")
        s1, s2 = tournamentSelect(li)
        #print(f'Parent 1: {s1[0]} (f: {s1[1]})')
        #print(f'Parent 2: {s2[0]} (f: {s2[1]})')
    
        #print("- crossover")
        offspring = onepointCrossover(s1, s2)
        o_list.append([offspring, offspring.count("1")])
        #print(f'Offspring: {offspring} (f: {offspring.count("1")})')
        
        bitFlipMutation(li)
        
    for i in o_list:
        m = list(x[1] for x in li)
        minx = min(m)
        mini = m.index(minx)
        if minx < i[1]:
            li[mini] = i
        
    cnt += 1