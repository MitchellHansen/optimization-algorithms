from subprocess import check_output
import subprocess
import random
import matplotlib.pyplot as plt
import time

random.seed()

loc = "../build/Lab4"

f = open('out','w')
f.write("Timer values")

for function in range(6, 9):
	print("Method: " + str(function))
	for q in range(0, 15):
		print("Function: " + str(q))
		f.write(str(q) + "\n")
		start = time.time()

		subprocess.call([
			loc,
			str(q),
			str(20),
			str(random.randint(0, 2147483646)),
			str(function)
		]) 

		end = time.time()
		f.write(str(end-start) + "\n")
		




f.close()



















