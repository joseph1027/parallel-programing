More details about the HW3 please refer to the course website.
http://people.cs.nctu.edu.tw/~ypyou/courses/PP-f17/assignments/HW3.pdf
 
[submit format]
Zip your code prime.c(or prime.cpp) and integrate.c(integrate.cpp)
Upload [HW3_your student id].zip to E3
[20171125]
If you have already upload your file, you don't need to renmae your zip file.
 
[Output]
DO NOT modifiy any output message!!
 
[Important]
SSH Passphrase
You must set up ssh passphrase to use 4 MPI nodes.
Instructions of set up are in the document
 
You can test your configuration with a hellow world program
https://github.com/wesleykendall/mpitutorial/blob/gh-pages/tutorials/mpi-hello-world/code/mpi_hello_world.c
 
If we execute it from node "host(pp1)" with another 3 nodes
You should see:
pp1 [/u/gcs/105/xxxxxxx] -xxxxxx- % mpiexec -np 4 --host host,slave1,slave2,slave3 ./mpi_hello_world
Hello world from processor pp1.cs.nctu.edu.tw, rank 0 out of 4 processors
Hello world from processor pp2.cs.nctu.edu.tw, rank 1 out of 4 processors
Hello world from processor pp3.cs.nctu.edu.tw, rank 2 out of 4 processors
Hello world from processor pp4.cs.nctu.edu.tw, rank 3 out of 4 processors
 
[Score]
70% = Correct output on a multiple node used condition.(Each program for 35%)
15% = Scalability(More node should decrease time used)
15% = Contest with your classmate(Using 4 MPI nodes)
 
Late submission has penalty of 15 points every day.
 
[20171118]
We have some connection problem on pp1
You can still set up ssh passphrase on another 3 nodes.(It will still work for pp1 after we fix connection problem)
You can still test your code by executing it on other nodes.
Ex:     execute on slave1(pp2)
pp2 [/u/gcs/105/xxxxxxx] -xxxxxx- % mpiexec -np 3 --host slave1,slave2,slave3 ./mpi_hello_world
Hello world from processor pp2.cs.nctu.edu.tw, rank 0 out of 3 processors
Hello world from processor pp3.cs.nctu.edu.tw, rank 1 out of 3 processors
Hello world from processor pp4.cs.nctu.edu.tw, rank 2 out of 3 processors

[20171120]
Connection problem on pp1 has been solved.

[20171129]
You should show output result by only one Node
