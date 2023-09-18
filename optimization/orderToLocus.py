order_based = input("Order_based: ")
locus_based = ""
for i in range(10):
    x = order_based.find(str(i))
    locus_based += order_based[x+1 if x < 9 else x-9]
print("Locus_based:", locus_based)
