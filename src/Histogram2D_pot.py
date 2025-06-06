import sys
import pandas as pd
import matplotlib.pyplot as plt

data=pd.read_csv(sys.argv[1])

x=data['xbin_center']
y=data['ybin_center']
z=data["count"]

plt.figure(figsize=(8,6))
plt.tricontourf(x,y,z,levels=100,cmap='viridis')
plt.colorbar(lable='counts')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('2D_Histogram')
plt.tight_layout()
plt.show()