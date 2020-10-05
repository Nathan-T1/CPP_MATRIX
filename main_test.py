
import test
import time
import numpy as np 

#a = np.array([[1.,2.],[17.,15.]])
#b = np.array([[2.,1.],[7.,5.]])
a = np.random.rand(10,10) 
b = np.random.rand(10,10)

start = time.time()
for i in range(0,10000):
    test.func(a, b)
end = time.time()
print(end - start)

start = time.time()
for i in range(0,10000):
    c = np.matmul(a, b)
end = time.time()
print(end - start)