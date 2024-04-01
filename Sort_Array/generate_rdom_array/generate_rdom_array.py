import random
import os


n = int(input("Enter number of element that the array have: "))
f = open('data.txt', 'w')
for i in range(0, n):
    if (i==n-1):
        f.write("{}".format(random.randint(0,101)))
    else:
        f.write("{}\n".format(random.randint(0,101)))

f.close()