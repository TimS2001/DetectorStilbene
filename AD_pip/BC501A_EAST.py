import math

BIN_L = 5 #light
MAX_L =  1200  #light

def LightConv(Energy):
    k = [3.285, 103.4, 0.03017, 1.00428]
    Light = k[0] * Energy - k[1] * (1.0 - math.exp(- k[2] * math.pow(Energy, k[3])))
    return Light * 1000

def EnergyConv(Light):
    power = 0.7009
    koef = 0.02547
    Energy = koef * math.pow(Light, power)
    return Energy


def GetResolution(Light):
    Energy = EnergyConv(Light)

    B = [14.29, 126, 81]
    Power = [1.5, 3.0]
    
    Resolution = math.sqrt(B[0] + B[1] * math.pow(Energy, Power[0]) + B[2] * math.pow(Energy, Power[1]))

    return  Resolution #percent