The following guide is really important, please read it more than twice!

More details about the HW2 please refer to the course website.
http://people.cs.nctu.edu.tw/~ypyou/courses/PP-f17/assignments/HW2.pdf
Note: Please see the "README" file inside the source directory.


[Submit Format]
Only submit the "[student ID].c", which rename from your "cg.c".
For example, my student ID is 0123456, and I will submit "0123456.c", which rename from your "cg.c".
 
[Expected Output]
Do not modify any output message from original "cg.c".
We will test your cg.c with the original project.
If the expected output is different from the original one, you will get zero score.
We will extract some key words from it to verfify your submission.
No further argument.

[How to execute the provided project, downloaded from the course website]
$ tar -xvf /path/to/the/tar/you/downloaded
$ cd CG
$ make clean && make DATASIZE=LARGE    #comments: please refer to the README inside the project directory.
$ ./bin/cg
 
 
[Score]
70% = The same output as the project we provided and you have add OpenMP code inside it
15% = Scalability(Speed: "4 core > 2 core > 1 core" are all required, failed and this 15% will be zero score.)
15% = Contest with your classmate (Grade is given by you speed rank using 4 core in the system)
Total = 100 score.

Penality for late submission after the due date will be 15(not 15%) for one day.
For example, you original score is 90 with 2 days delay after due date, and you will get 60(90-15*2) as your real score.
No further argument.

[Evaluation] 
Use taskset to limit the CPU that the process can see
$ cd /path/to/CG

The following commands are what we will use to evaluate the time consuming for your submission.



For one core
$ taskset -c 0 ./bin/cg

For two core
$ taskset -c 0,1 ./bin/cg

For four core
$ taskset -c 0,1,2,3 ./bin/cg

A simple way to see how many threads you are using during OpenMP code region:
#pragma omp parallel
{
printf("num=%d\n", omp_get_num_threads());
}
 


 
[Platform]
CSCC provide 4 servers for PP course.
Use you CSCC account to ssh into it(port:22).
IP:
pp1.cs.nctu.edu.tw
pp2.cs.nctu.edu.tw
pp3.cs.nctu.edu.tw
pp4.cs.nctu.edu.tw
