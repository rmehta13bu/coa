import os

with open('../programs/memory_map.txt', 'r') as f:
    data = f.read()
    data = data.split(" ")

with open('../programs/temp.txt', 'w') as w:
    for i in range(len(data)):
        w.writelines(data[i]+ "\n")
# print(int(data[189*4])-int(data[105*4]))