import random

N_NUM = 10

def makeTree(start, end):
    # 트리의 간선을 랜덤하게 생성하는 함수
    edges = []
    for i in range(start+1, end+ 1):
        j = random.randint(start, i - 1)
        edges.append([i, j])
    return edges

t1 = makeTree(1, N_NUM//2)
t2 = makeTree((N_NUM//2+1), N_NUM)

edges = t1 + t2 + [[(N_NUM//2+1), 1]]

#파일 쓰기
file_name = './data/tree%d.txt'%N_NUM

with open(file_name, 'w+') as file:
    for num, i in enumerate(edges):
        if num+1 < len(edges):
            file.write(' '.join(map(str, i)) + "\n")
        else:
            file.write(' '.join(map(str, i)))