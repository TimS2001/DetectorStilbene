
from AD_pip.AD_converter import ReadAndConvert
from AD_pip.BC501A import LightConv, EnergyConv, GetResolution, BIN_L, N
from AD_pip.Plotting import plotHist
from AD_pip.Convertion import ConvertToEnergy
import numpy as np
import math

def MyLightConv(Energy):
    return Energy
def MyResolution(Energy):
    if(Energy == 0):
            return 0
    B = [14.29, 126, 81]
    Power = [-1.5, -3.0]
    
    Resolution = math.sqrt(B[0] + B[1] * math.pow(Energy, Power[0]) + B[2] * math.pow(Energy, Power[1])) #percentage
    return Resolution / 100 #proportion
MyBin = 0.01 #MeV
MyN = 1600

def MyPrint(Hist, str):
    f = open(str, 'w')
    bin = Hist[0][2] - Hist[0][1]
    tmp_str = np.str_(0) + '\t' + np.str_(0) + '\n'
    f.write(tmp_str)
    for i in range(1, len(Hist[0])):
        tmp_str = np.str_(Hist[0][i] - 0.01) + '\t' + np.str_(Hist[1][i] / bin) + '\n'
        f.write(tmp_str)
    f.close()

def MyEnergyConv(Energy):
    def f(Hist):
        NewHist = [np.zeros(len(Hist[0])), np.copy(Hist[1])]
        for i in range(0, len(Hist[0])):
            NewHist[0][i] = Energy(Hist[0][i])
        return NewHist
    return f

str = 'data/detector_data.txt'   
Hist = ReadAndConvert(str, MyLightConv, MyResolution, MyBin, MyN)

#Hist = ReadAndConvert(str, LightConv, GetResolution, BIN_L, N)
#Hist = ConvertToEnergy(Hist, MyEnergyConv(EnergyConv), MyBin, MyN)
MyPrint(Hist, 'DT1.txt')
plotHist(Hist)
#Hist1 = LGHT.ReadAndBlur(str)
