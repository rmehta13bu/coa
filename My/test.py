import os

with open('./programs/memory_map.txt', 'r') as f:
    data = f.read()

data = data.split(" ")
print(len(data))
# print(data[60552])
print(data[6368//4])
# print(int(data[189*4])-int(data[105*4]))