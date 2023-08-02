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


import matplotlib.pyplot as plt
import numpy as np

# Generate some data...
data = np.random.random((100, 5))
y = data.mean(axis=0)
x = np.random.random(y.size) * 10
x -= x.min()
x.sort()

# Plot a line between the means of each dataset
plt.plot(x, y, 'b-')

# Save the default tick positions, so we can reset them...
locs, labels = plt.xticks() 

plt.boxplot(data, positions=x, notch=True)

# Reset the xtick locations.
plt.xticks(locs)
plt.show()
#print(np_arr)