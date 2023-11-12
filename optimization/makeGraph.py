import random

N_NUM = 100 #노드 크기
N = 30  # 최적해

edges = []

for i in range(1, (N_NUM/2)+1):
    for j in range(i+1, (N_NUM/2)+1):
        if i != j:
            edges.append([j, i])
            
for i in range((N_NUM/2)+1 , N_NUM+1):
    for j in range(i + 1, N_NUM+1):
        if i != j:
            edges.append([j, i])
            
li1 = [i for i in range(1, (N_NUM/2)+1)]
li2 = [i for i in range((N_NUM/2)+1, N_NUM+1)]

choice1 = random.sample(li1, N)
choice2 = random.sample(li2, N)

for i in range(N):
    edges.append([choice1[i], choice2[i]])
   
#파일 쓰기
file_name = './data/%d.txt'%N_NUM

with open(file_name, 'w+') as file:
    for num, i in enumerate(edges):
        if num+1 < len(edges):
            file.write(' '.join(map(str, i)) + "\n")
        else:
            file.write(' '.join(map(str, i)))