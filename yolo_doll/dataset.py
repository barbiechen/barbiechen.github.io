import os
import random

trainval_percent = 0.9  #train 和 val 占整個照片數量的比例
train_percent = 0.8     #train 站train和val的比例
filepath = '..\images\label' #照片label完後存放文字檔的位置(且位置的資料夾裡不能含有照片檔，不然會重複讀取檔名)

txtsavepath = '..\images\train_val_test_label' #分類之後txt檔存放的位置
total_file = os.listdir(filepath)

num = len(total_file)
list = range(num)
t_v = int(num*trainval_percent)
tr = int(t_v*train_percent)
trainval = random.sample(list,t_v)
train = random.sample(trainval,tr)

#以下為四種檔案存放的位置和檔名
ftrainval = open('../images/train_val_test_label/trainval.txt','w') 
ftest = open('../images/train_val_test_label/test.txt','w')
ftrain = open('../images/train_val_test_label/train.txt','w')
fval = open('../images/train_val_test_label/val.txt','w')

for i in list:
    name = total_file[i][:-4] +'\n'
    if i in trainval:
        ftrainval.write(name)
        if i in train:
            ftrain.write(name)
        else:
            fval.write(name)
    else:
        ftest.write(name)
ftrainval.close()
ftrain.close()
fval.close()
ftest.close()
        
