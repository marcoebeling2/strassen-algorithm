import subprocess
import random
import time

# set random seed
random.seed(time.time())

# file to write data to
file = open("input.txt", "w+")

# compile
subprocess.run(['g++', 'main.cpp', 'strassen.cpp', '-o', 'myfile'])

# lists to hold data
sizeList = []
bruteForceList = []
divideAndConquerList = []
strassenList = []

# complete 8 times
for i in range(2, 10, 1) :
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

    # add data to lists
    sizeList.append(size)
    runTimeFile = open("run_time.txt", "r")
    line = runTimeFile.readline()
    nums = str(line).split()
    bruteForceList.append(nums[0])
    divideAndConquerList.append(nums[1])
    strassenList.append(nums[2])
    runTimeFile.close()



# out put data
runTimeFile = open("run_time.txt", "w+")
runTimeFile.write("  n | brute-force | divide-and-conquer | strassen\n")
for i in range(0, len(sizeList), 1) :
    runTimeFile.write("%3d | %11d | %18d | %8d\n" % (sizeList[i], int(bruteForceList[i]), int(divideAndConquerList[i]), int(strassenList[i])))
runTimeFile.close()