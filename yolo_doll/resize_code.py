from PIL import Image
import os
from resize import fill_img
filepath = '..\images\label'
total_file = os.listdir(filepath)
num = len(total_file)
pic_w = 416     #照片寬
pic_h = 416     #照片高




for i in range (num):
    img_name = total_file[i][:-4]
    img = Image.open('../images/pic_dolls/Winne_the_pooh/%s.jpg'%img_name)
    w = img.width
    h = img.height
    if w==h:
        img = img.resize((pic_w, pic_h), Image.ANTIALIAS)
    else:
        longer_side = max(img.size)
        horizontal_padding = (longer_side - img.size[0]) / 2
        vertical_padding = (longer_side - img.size[1]) / 2
        img = img.crop((
        -horizontal_padding,
        -vertical_padding,
        img.size[0] + horizontal_padding,
        img.size[1] + vertical_padding
        ))
        img = img.resize((pic_w,pic_h), Image.ANTIALIAS)
        
    img.save('../images/pic_dolls/new/%s.jpg'%img_name)
