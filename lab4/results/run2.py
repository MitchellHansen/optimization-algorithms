from subprocess import check_output
import subprocess
import random
import matplotlib.pyplot as plt
import time

random.seed()

loc = "../build/Lab4"

search = 8

for function in range(0, 15):

	print("Function: " + str(function))	
	for q in range(0, 10):
		subprocess.call([
			loc,
			str(function),
			str(20),
			str(random.randint(0, 2147483646)),
			str(search)
		]) 
















