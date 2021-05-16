import xml.etree.ElementTree as ET
from os import getcwd
sets = ['train', 'val', 'test'] #定義資料集名稱

classes = ['WinnieThePooh','Piglet','Tigger','Eeyore','MickeyMouse','MinnieMouse','Stitch'
      ,'ChipOrDale','DonaldDuck','Dunbo',"Lost-O'-HuggingBear",'DaisyDuck'] #定義自訂義類別名稱

def convert_annotation(img_id, list_file):
    in_file = open('../images/label_new/%s.xml' %img_id, encoding='utf-8') #指定標註檔路徑
    tree=ET.parse(in_file)
    root = tree.getroot()

    for obj in root.iter('object'):
        difficult = obj.find('difficult').text
        cls = obj.find('name').text
        if cls not in classes or int(difficult)==1:
            continue
        cls_id = classes.index(cls)
        xmlbox = obj.find('bndbox')
        b = (int(xmlbox.find('xmin').text), int(xmlbox.find('ymin').text), int(xmlbox.find('xmax').text), int(xmlbox.find('ymax').text))
        list_file.write(" " + ",".join([str(a) for a in b]) + ',' + str(cls_id))

for image_set in sets:
    img_names = open('../images/train_val_test_label/%s.txt'%image_set).read().strip().split() #指定待轉換清單檔案名稱
    list_file = open('../data/final_%s.txt'%image_set, 'w') #指定轉換完成清單名稱
    for img_name in img_names:
        list_file.write('../images/pic_dolls/new/%s.jpg'%img_name)
        img_id = img_name.split('.')
        convert_annotation(img_id[0], list_file)
        list_file.write('\n')
    list_file.close()
