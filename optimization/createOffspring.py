from random import randrange
LEN = 10 #The length of a chromosome 

#parent 입력
p1 = input("Parent1: ")
p2 = input("Parent2: ")

#random cut point 생성
cut_point = randrange(LEN+1)

#offspring 출력
print("Cut point: before index", cut_point)
print("Offspring1:", p1[0:cut_point]+p2[cut_point:LEN])
print("Offspring2:", p2[0:cut_point]+p1[cut_point:LEN])
