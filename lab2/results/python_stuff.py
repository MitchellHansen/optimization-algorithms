from subprocess import check_output
import subprocess
import random
import matplotlib.pyplot as plt
import time

random.seed()

loc = "../build/Lab2"

f = open('out','w')

function = "1"

print("dim=10")
f.write("dim=10\n")
for q in range(0, 30):

	subprocess.call([
		loc,
		str(13),
		str(10),
		str(random.randint(0, 2147483646)),
		function
	]) 
	


#print("dim=10")
#f.write("dim=10\n")
#for q in range(0, 15):
#	if q == 4 or q == 12:
#		continue
#	print(q)
#	start = time.time()
#	
#	subprocess.call([
#		loc,
#		str(q),
#		str(10),
#		str(random.randint(0, 2147483646)),
#		function
#	]) 
#	
#	end = time.time()
#	f.write(str(end-start) + "\n")
#	print(end - start)
#
#print("dim=20")
#f.write("dim=20\n")
#for q in range(0, 15):
#	if q == 4 or q == 12:
#		continue
#	print(q)
#	start = time.time()
#	
#	subprocess.call([
#		loc,
#		str(q),
#		str(20),
#		str(random.randint(0, 2147483646)),
#		function
#	]) 
#	
#	end = time.time()
#	f.write(str(end-start) + "\n")
#	print(end - start)

#print("dim=30")
#f.write("dim=30\n")
#for q in range(0, 15):
#	if q == 4:
#		continue
#	print(q)
#	start = time.time()
#	
#	subprocess.call([
#		loc,
#		str(q),
#		str(30),
#		str(random.randint(0, 2147483646)),
#		function
#	]) 
#	
#	end = time.time()
#	f.write(str(end-start) + "\n")
#	print(end - start)






f.close()



















