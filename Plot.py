import AD_pip.AD_converter as conv
import AD_pip.Plotting as plot
import AD_pip.Analysis as anl
import numpy as np
import AD_pip.AD_converter_Energy_version as conv1

str = 'data/detector_data.txt' # файл чтения   

#Hist = conv1.ReadAndBlur(str)
Hist = anl.Convert_To_Energy(conv.ReadAndBlur(str))
#Hist1 = LGHT.ReadAndBlur(str)
###

str1 = 'data/Resp_1.88 MeV.dat'
def print1(Hist, str):
    N = len(Hist[0])
    with open(str, "w") as file:
        for i in range(0, N - 1):
            file.write(np.str_(Hist[0][i]))
            file.write("\t")
            file.write(np.str_(Hist[1][i]))
            file.write("\t")
            file.write('0')
            file.write("\n")
print1(Hist, str1)
#'''

#plot.plotHist(TmpHist, 'MySpect')
#plot.plotHist(Hist1, 'MySpect')

#plot.plotHistdiff(Hist, Hist1, 'MySpect')

plot.plotAndFind(Hist, 'MySpect') 