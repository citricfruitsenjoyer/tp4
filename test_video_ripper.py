import cv2
import numpy as np
names=['videos/20250528_170906-003.mp4','videos/20250528_173138.mp4','videos/20250528_173920.mp4','videos/20250528_175822.mp4',
       'videos/C1862.MP4','videos/C1871.MP4','videos/C1872.MP4','videos/C1873.MP4','videos/C1883.MP4','videos/C1888.MP4','videos/C1889.MP4',
       'videos/C1896.MP4','videos/C1897.MP4','videos/C1899.MP4','videos/C1906.MP4','videos/C1907.MP4',
       'videos/C1910.MP4','videos/C1915.MP4','videos/C1917.MP4','videos/C1918.MP4'] #arranca en 12 
import time
import os

start=time.time()

i=0

path = 'X:/vid/C1917.MP4'

vidcap = cv2.VideoCapture(path)
success, image = vidcap.read()
count = 0

# Ensure output folder exists
# os.makedirs(f"frames_video{i}", exist_ok=True)

while success:
    # Save frame with zero-padded numbers (e.g., frame0001.jpg)
    # cv2.imwrite(f"frames_video{i}/frame{count:06d}.jpg", image)
    success, image = vidcap.read()
    # np.sum(image[:1000,:600,0])
    count += 1
vidcap.release()
print(f'the end {i}',time.time()-start)
    