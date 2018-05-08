import cv2
import numpy as np

img = cv2.imread(r'C:\Users\tchat\.spyder-py3\bumblebee.jpg')
gray= cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

sift = cv2.xfeatures2d.SIFT_create()
kp = sift.detect(gray,None)

img=cv2.drawKeypoints(img,kp, None, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
cv2.imwrite('D:\Image Processing\HW3\sift_bum_keypoints.jpg', img)

surf = cv2.xfeatures2d.SURF_create(4000)
(kps, descs) = surf.detectAndCompute(gray, None)

img1=cv2.drawKeypoints(gray,kps, None, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
cv2.imwrite('D:\Image Processing\HW3\surf_bum_keypoints.jpg', img1)

