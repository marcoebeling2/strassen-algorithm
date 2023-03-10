# strassen-algorithm
-In strassen.cpp, I create three method of 2D Matrix Multiplication, brute-force, "divide-and-conquer", and strassen algorithm. The respective run times for brute-force, "divide-and-conquer", and strassen algorithm are O(3), O(3), O(2.718).

-In main.cpp, I use the methods from strassen.cpp to complete matrix multiplication from the matrices in input.txt. During this process, I measure the time required to run these methods.

-In strassen.py, I script the execution of the main.cpp for random matrices of size 4-512, increasing by a factor of two each time. The final output for each 512 x 512 matrix are displayed in brute_force.txt, divide_and_conquer.txt, and strassen.txt. 

-In run_time.txt, I record the run times for each method given the matrix size. The strassen method ran quicker "divide-and-conquer", as evident by run times previously stated. The run time for brute-force method is signifigantly faster because the brute-force method does not spend time allocating and deallocating. However, as the size of the matrix increases, strassen method becomes quicker.
