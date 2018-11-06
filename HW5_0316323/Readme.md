[作業繳交格式]
一個HW5_XXXXXXX.zip 不包含任何directory。
histogram.cl 是給你寫OpenCL kernel，方便你開發。
助教預期輸入下列指令，要能有以下行為(只產生2個作業檔案，檔名為histogram.cpp及histogram.cl)：(XXXXXXX表示學號)
%unzip HW5_XXXXXX.zip
Archive:  HW5_XXXXXXX.zip
  inflating: histogram.cpp
  inflating: histogram.cl
 
[預期輸出格式]
請依照原先提供尚未平行化的版本輸出到檔案(studne_ID.out 假設學號是0555555，則輸出為0555555.out)，除了執行時間不同之外，輸出內容都要一樣。
OpenCL直接輸出在終端機上的資訊沒關係，但輸出的.out檔內容一定要一樣。
如果.out檔輸出不符合預期，就會拿到0分，也不能補交。
底下的作業說明，請確保你的輸出符合預期。
 
[評分方式]
正確性：75%
速度(與全班同學一同比較，非原始版本)：25%
我們每次作業都有檢查你是不是真的有用到對應的平行技術(本次是OpenCL)，有才會給分，沒有就是0分。
以上共100分，遲交1天扣15分，不能補交。
編譯指令：g++ -o histogram histogram.cpp -lOpenCL
 
平台：同HW4，user/pwd都同HW4
IP: 140.113.215.195    port:32403,32404,32414,32428
 
[作業說明]
此次作業有可能發生比原本未平行化的版本還慢的可能，因此我們會用較大的input來進行測試，也會看同學是否有真的用到OpenCL寫作業，才進行排名。
因為檔案較大，而硬碟空間有限，因此我們統一提供幾個input供同學參考，請確保你的作業跑這幾個測資可以得到預期的答案，在/home/data/solution底下有預期答案。
測試檔案及解答放在 /home/data 底下，請勿嘗試移除或修改/home/data底下的資料，直接看檔名就可以知道對應的參考解答是哪個：
/home/data/OpenCL/input-1307M         對應的預期輸出      /home/data/OpenCL/ReferenceOutput/output-1307M
/home/data/OpenCL/input-2532M         對應的預期輸出      /home/data/OpenCL/ReferenceOutput/output-2532M
/home/data/OpenCL/input-38M             對應的預期輸出     /home/data/OpenCL/ReferenceOutput/output-38M
/home/data/OpenCL/input-674M           對應的預期輸出      /home/data/OpenCL/ReferenceOutput/output-674M
 
[如何使用助教提供的測試檔案]
1. 切換到有你的作業可執行檔的目錄後   % mkfifo input
2. 挑一個你要使用的測資，以38M為例   % cat /home/data/OpenCL/input-38M > input &
3. 執行你的作業  % ./histogram
4. 得到作業輸出後，刪除剛剛建立的input   % rm input
5. 檢查輸出是否符合預期 % diff ./xxxxxx.out  /home/data/OpenCL/ReferenceOutput/output-38M
6. 輸出都一樣的話，diff不會顯示任何資訊，這樣才是對的
7. 你可以重複1~5來測試不同測資
