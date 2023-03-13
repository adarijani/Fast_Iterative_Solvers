import pandas as pd
FILENAME=input()
data = pd.read_csv(FILENAME,sep='\s+',header=None)
data = pd.DataFrame(data)
import matplotlib.pyplot as plt
x = data[0]
y = data[1]
plt.yscale('log')
plt.title(FILENAME)
plt.xlabel("multigrid iteration number")
plt.ylabel("relative infinity error")
plt.plot(x, y,'k+')
plt.savefig(FILENAME + ".pdf")
