import cv2
import numpy as np

img = cv2.imread('D:\Image Processing\Optimus_Prime.jpg')
gray= cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

sift = cv2.xfeatures2d.SIFT_create()
kp = sift.detect(gray,None)

img=cv2.drawKeypoints(gray,kp, None, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
cv2.imwrite('D:\Image Processing\HW3\sift_OP_keypoints_gray.jpg', img)

surf = cv2.xfeatures2d.SURF_create(4000)
(kps, descs) = surf.detectAndCompute(gray, None)

img1=cv2.drawKeypoints(gray,kps, None, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
cv2.imwrite('D:\Image Processing\HW3\surf_OP_keypoints.jpg', img1)

