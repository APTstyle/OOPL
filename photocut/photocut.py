import cv2

# 讀取圖檔
img = cv2.imread("Huntresssprite_1.9.0.webp.png")
print(img.shape) #偵測圖片大小
# 裁切區域的 x 與 y 座標（左上角）
x = 0
y = 0
perw = 12#寬
perh = 15#高
count = 1
for i in range(1,8):
	for j in range(1,22):
		w = perw*j # 裁切區域的長度與寬度
		h = perh*i
		crop_img = img[h-perh:h, w-perw:w] # 裁切圖片
		#cv2.imshow("cropped", crop_img) # 顯示圖片
		cv2.waitKey(0)
		Img_Name = "./result/" + str(count) + "Badgesheet.png"
		print(Img_Name)
		cv2.imwrite(Img_Name, crop_img)# 寫入圖檔
		count += 1