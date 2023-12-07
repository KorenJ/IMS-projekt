import json

import numpy as np
import matplotlib.pyplot as plt

file1 = open("../output/speedmax1.txt", 'r')
file2 = open("../output/speedmax2.txt", 'r')
file3 = open("../output/speedmax3.txt", 'r')
data = []
array1 = file1.readline().split()
array1.append('2')
array2 = file2.readline().split()
array2.append('5')
array3 = file3.readline().split()
array3.append('9')
data.append(list(map(float, array1)))
data.append(list(map(float, array2)))
data.append(list(map(float, array3)))

plt.figure(figsize=(5, 5))
for k, row in enumerate(data):
    x = np.linspace(0, 1, 1000)
    y = []
    for i in range(len(row) - 1):
        y.append(np.round(((row[i] / row[-1]) * 100), 1))
    plt.fill_between(x, y, alpha=0.1)
    plt.plot(x, y, label=rf'Rychlost $v{k+1}_' + '{' + 'max' + '}$' + rf'$= {int(row[-1])}$')
plt.xlabel(r'Počáteční hustota provozu $p$')
plt.ylabel(r'Podíl maximální rychlosti a průměrné rychlosti v %')
plt.ylim((0,100))
plt.legend(loc='upper right')

plt.savefig("../output/maxspeed.png")
