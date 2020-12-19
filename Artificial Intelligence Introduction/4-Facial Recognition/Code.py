# 18080128 孙晨伟
import cv2

image = cv2.imread("a.jpg")  ##导入照片  a.jpg b.jpg c.jpg
classifier = cv2.CascadeClassifier("classifier.xml")  # 人脸检测分类器
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)  # 读取图像
faces = classifier.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))  # 识别人脸
print("人脸数量：{}".format(len(faces)))  # 输出结果
for (x, y, w, h) in faces:  # 标出人脸
    cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 3)
cv2.imshow("Result:", image)
cv2.waitKey(0)
