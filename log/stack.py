import numpy as np
arr = []
a=[1,2,3,4]
b=[5,6,7,8]
c=[]
d=[]
#d=[a,b,a]
for i in range (4): 
    d.append(i)
print(len(d))

for i in range (3):
    c.append(d)

#print(c)

c_arr = np.array(c)

print(len(c_arr))


#print(np_arr)