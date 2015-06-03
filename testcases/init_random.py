import random
import sys
file_name = sys.argv[1]
l = random.randint(5000,10000)
f = open(file_name, 'w')
# max_x = 600, max_y = 800
f.write(str(l) + '\n')
for i in range(l):
	f.write(str(random.randint(0,799)) + ' ' + str(random.randint(0,599)) + '\n')
f.close()