import numpy as np

data = np.load('RGB_cameraintrinsic_parameters.npz')
mtx = data['mtx']      # 相机内参矩阵
dist = data['dist']    # 畸变系数

print("mtx:", mtx)
print("dist:", dist)