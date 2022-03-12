# image-process
台科大 色彩及影像實作技術 OpenCV 基本影像處理

1. 讀取兩張彩色影像檔(解析度不要太高，內容自行選擇)。
2. 顯示這兩張影像(im1, im2)。需要用到imread, namedWindow, moveWindow,imshow 等函式。
3. 用resize，將im1 高寬各縮小一倍，得到im3。
4. 用resize，將im2 的大小縮到跟im3 一樣大，名為im4。
5. 建立與im1 一樣大小的影像im5。
6. 在指令視窗顯示im1 至im5 的size。
7. 將im3 與im4 經過多種處理(自行決定)，貼入im5: 以下圖im5 為例，分別貼了(1)Sobel 線偵測，(2) blur，(3) im3 與im4 以0.5:0.5 將兩圖融合，(4)反白。
8. 可按照此例，使用不同的處理方式處理個別子影像(例如：邊緣偵測、色調分離等)。可能需要用到roi 設定，以及copyTo，clone，blue, Sobel,convertScaleAbs, addWeighted 等函式。
9. 顯示多圖拼貼的im5 後，用setMouseCallback 函式，讓滑鼠左鍵點擊im5 的任意位置。用putText 函式，標註自己的學號。並用imwrite 函式儲存當下的影像。
注意：onMouse 函式內使用的Mat 物件，必須是全域物件(也就是在主程式的外部宣告)。
10. 步驟9 可重覆運行，直到按ESC 鍵離開程式。
11. 加入滑桿，控制影像中的某些參數，例如下頁圖例中，控制字的大小。

![](https://github.com/naiyu0609/image-process/blob/main/1.PNG)
![](https://github.com/naiyu0609/image-process/blob/main/2.PNG)
