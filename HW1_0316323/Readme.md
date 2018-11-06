 1. 關於input 參數
請讓你的程式能夠接受兩個參數
第一個是 環境cpu 數目
第二個是 執行的次數
eg:
./pi 4 10000

2. 
若你測試scalability
為了讓你的程式可以在指定的Cpu數目下執行
可以使用taskset -c [a numerical list of processors] command
eg:
taskset -c 1,2 ./pi 2 100000
綁定程式在第1,2 core上執行

"Your program should be scalable."，意思是我們測試的時候會讓同學們的程式分別跑在1 core, 2 cores, 4 cores的不同環境下，不要求一定要達到2倍或4倍的speedup，但在多核心的環境下仍需有較好的 performance，此項目也會列入評分。
 
2. 關於output結果
請大家直接輸出 pi_estimate 結果, eg:
3.1415926

TIPS: pi_estimate 在執行1000萬次後大概會準確到 3.14XXX。
 
3. 關於ToolChain
我們會用以下指令 compile 同學們的程式碼:
 
C++:
g++ -pthread -std=c++11 -O2 -s pi.cpp -o pi
 
或

C:
gcc -pthread -std=gnu99 -O2 -s pi.c -o pi
 
gcc 版本爲 7.2.0
 

3.測試環境
 
四核心PC
OS為Intel(R) Xeon(R) CPU X5675
