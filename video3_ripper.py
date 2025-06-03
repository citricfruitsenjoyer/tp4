import cv2
names=['videos/20250528_170906-003.mp4','videos/20250528_173138.mp4','videos/20250528_173920.mp4','videos/20250528_175822.mp4','videos/C1862-001.MP4']
import time
import os

start=time.time()

# for i in range(1,2):
#     vidcap = cv2.VideoCapture(names[i-1])
#     success, image = vidcap.read()
#     count = 0

#     # Ensure output folder exists
#     os.makedirs(f"frames_video{i}", exist_ok=True)

#     while success:
#         # Save frame with zero-padded numbers (e.g., frame0001.jpg)
#         cv2.imwrite(f"frames_video{i}/frame{count:06d}.jpg", image)
#         success, image = vidcap.read()
#         count += 1
#     vidcap.release()
#     print(f'the end {i}',time.time()-start)

for i in range(5,6):
    print(names[i-1])
    vidcap = cv2.VideoCapture(names[i-1])
    success, image = vidcap.read()
    count = 0

    # Ensure output folder exists
    os.makedirs(f"frames_video{i}", exist_ok=True)

    while success:
        # Save frame with zero-padded numbers (e.g., frame0001.jpg)
        cv2.imwrite(f"frames_video{i}/frame{count:06d}.jpg", image)
        success, image = vidcap.read()
        count += 1
    vidcap.release()
    print(f'the end {i}',time.time()-start)