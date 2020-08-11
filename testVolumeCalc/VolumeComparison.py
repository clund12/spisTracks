import sys
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

path = '~/geant4/work/spisTracks/testVolumeCalc/'


offsetAlongFace = pd.read_csv(path+'OffsetAlongFace.csv', header=0, index_col=False)
offsetAlongFace.columns = ['offset', 'Along face']

offsetAlongDiagonal = pd.read_csv(path+'OffsetAlongDiagonal.csv', header=0, index_col=False)
offsetAlongDiagonal.columns = ['offset', 'Along planar diagonal']

offsetAlongFullDiagonal = pd.read_csv(path+'OffsetAlongFullDiagonal.csv', header=0, index_col=False)
offsetAlongFullDiagonal.columns = ['offset', 'Along full diagonal']

offsetAnalytic = pd.read_csv(path+'OffsetAnalytical.csv', header=0, index_col=False)
offsetAnalytic.columns = ['offset', 'Analytic']

################################################################################

#fig = plt.figure(figsize=(9,6))

combined = pd.concat([offsetAlongFace,offsetAlongDiagonal,offsetAlongFullDiagonal,offsetAnalytic],axis=1)
combined = combined.loc[:,~combined.columns.duplicated()]

combined.plot(x='offset',y=['Along face', 'Along planar diagonal', 'Along full diagonal','Analytic'],figsize=(9,6))

plt.xlabel('Centre-centre distance (1/radius)', fontsize=18)
plt.ylabel('Volume / non-overlapping volume', fontsize=18)
plt.legend(fontsize=16)
plt.title('Approximation of the volume of two overlapping spheres', fontsize=18)# using cubes', fontsize=18)

#plt.show()
plt.savefig('AVcomparison.png',
        format='png',
        dpi=500,
        bbox_inches='tight'
        )
