import cv2
import numpy as np
from matplotlib import pyplot as plt

img1 = cv2.imread(r'C:\Users\tchat\.spyder-py3\ferrari1.jpg')
img2 = cv2.imread(r'C:\Users\tchat\.spyder-py3\ferrari_2.jpg')

surf = cv2.xfeatures2d.SURF_create(3000)

(kp1, descs1) = surf.detectAndCompute(img1, None)
(kp2, descs2) = surf.detectAndCompute(img2, None)

bfm = cv2.BFMatcher()
match = bfm.knnMatch(descs1,descs2, k=2)

good = []
for m,n in match:
    if m.distance < 0.75*n.distance:
        good.append([m])
        
array = np.zeros((img1.shape[:2]))

img3 = cv2.drawMatchesKnn(img1,kp1,img2,kp2,good,array)

plt.imshow(img3),plt.show()
cv2.imwrite('D:\Image Processing\HW3\Ferrari1_Ferrari2_surfmatch.jpg', img3)