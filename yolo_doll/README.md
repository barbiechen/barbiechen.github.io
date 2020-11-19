Resize_code.py
把照片補成正方形並resize成自訂大小(我設定是416*416與到時訓練input image size大小一樣)
使用前須改:
照片的寬和高、要resize照片的路徑、resize後要存檔的路徑

Dataset.py 
把照片分成 train val test 三大類，並輸出成 train.txt val.txt test.txt
使用前須改:
檔案位置、存檔位置、val train 的比例
(詳細敘述都在py檔裡面附註了)

Voc_to_txt.py
把label的文字檔改成yolo的txt檔
使用前須改:
訓練classes的名字、要轉換的xml的路徑、在dataset.py分好的txt檔的路徑、輸出後儲存的路徑、照片相對train.py的路徑

Images 資料夾裡
Label資料夾: 沒有經過resize的xml檔
Label_new資料夾: resize過的xml檔
Pic_dolls資料夾裡:
New 資料夾: resize過的照片
Test資料夾: 一些切過等等的照片
Winne_the_pooh: 沒經過resize的照片
train_val_test_label資料夾: train.txt val.txt test.txt trainval.txt 

yolov3 資料夾裡:
	convert.py把權重檔改成keras的全重檔(.h5)，已轉換完放在data資料夾裡
	my_train.py 訓練檔
		需要改:
		一些檔的路徑(程式裡面都有附註)，照片大小、起始權重路徑、訓練後存檔權重路徑
	predict.py 預測檔(執行命令: python predict.py –image)
	yolo.py yolov3預測時會用import的package
  需要改: 使用權重檔的路徑
	Yolo3資料夾裡: yolo3一些作者寫的package
	
Data資料夾裡:
Final_test.txt final_train.txt final_val.txt是我test train val的三個yolo格式檔
My_classes.txt 我訓練娃娃的名字
Yolov3_doll.h5我訓練完後的權重
Yolo_weight.h5 tiny_yolo_weight.h5 作者的權重
Yolov4資料夾裡:
Predict.py train.py yolo.py 使用方法與v3差不多但不能通用
Data資料夾裡的內容與v3的差不多，我最後訓練好的權重檔為yolov4_doll.h5

