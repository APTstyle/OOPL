import cv2
import os
def cut(name):
	# 讀取圖檔
	img_name = name + ".png"
	img = cv2.imread(img_name)
	# 裁切區域的 x 與 y 座標（左上角）
	x = 0
	y = 0
	perw = 12#寬
	perh = 15#高
	count = 1
	if not os.path.isdir(name):
		os.mkdir(name)
	cv2.waitKey(0)
	for i in range(1,8):
		for j in range(1,10):
			w = perw*j # 裁切區域的長度與寬度
			h = perh*i
			crop_img = img[h-perh:h, w-perw:w] # 裁切圖片
			#cv2.imshow("cropped", crop_img) # 顯示圖片
			cv2.waitKey(0)
			Img_Name = "./" + name + "/" + name[:-1] + str(count) + ".bmp"
			print(Img_Name)
			cv2.imwrite(Img_Name, crop_img)# 寫入圖檔
			count += 1
def size(name):
	# 讀取圖檔
	img_name = name + ".png"
	img = cv2.imread(img_name)
	print(img.shape) #偵測圖片大小

def pngtobmp(name,n):#轉檔
	for i in range(1,n+1):
		img_name = name+str(i)+".png"
		img = cv2.imread(img_name)# 讀取圖檔
		cv2.waitKey(0)
		Img_Name_bmp = "./bmp/" + img_name[:-4] + ".bmp"
		x = img.shape[1]
		y = img.shape[0]
		crop_img = img[0:y, 0:x]
		cv2.imwrite(Img_Name_bmp, crop_img)
		#print(Img_Name_bmp)
		print("pngtobmp success")
#cv2.imshow("img", img) # 顯示圖片
cv2.waitKey(0)
work = str(input("Please enter cut,size or bmp\n"))
if work == "cut":
	name = str(input("Please enter filename\n"))
	cut(name)
elif work == "size":
	name = str(input("Please enter filename\n"))
	size(name)
elif work == "bmp" :
	name = str(input("Please enter filename without number\n"))
	n = int(input("How many file to wanna transform?\n"))
	pngtobmp(name,n)
else :
	print("Please enter cut,size or bmp!")
