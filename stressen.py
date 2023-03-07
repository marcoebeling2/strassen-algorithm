# in this file: make output in input.txt, run each method and gather data, plot the data for each one

import subprocess
import csv
import random
import time
import math

# set random seed
random.seed(time.time())


# file to write data to
file = open("input.txt", "w+")

# compile
subprocess.run(['g++', 'main.cpp', 'stressen.cpp', '-o', 'myfile'])

# complete 8 times
for i in range(2, 9, 1) :
    #create data to wrtie
    size = pow(2, i)
    # file to write data to
    file = open("input.txt", "w+")
    file.write(str(size) + "\n")
    # fill arrays now
    for i in range(size*2) :
        for j in range (size) : 
            file.write("%d " % random.randint(1, 4))
        file.write("\n")
    file.close()

    subprocess.run(['./myfile.exe'])

# read in data to find run time
