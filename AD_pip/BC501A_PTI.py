import math


BIN_L = 50 #light
MAX_L = 100e3 #light
MIN_L = 10 #light

k = [3.758, 5.145, 3.8608, 3.504]

B = 990
pw = 1.594

def LightConv(Energy):
    Light = k[0] * Energy - k[1] * (1.0 - math.exp(- k[2] * math.pow(Energy, k[3])))
    return Light * 1000

print(math.pow(B, -1. / pw))

def EnergyConv(Light):
    power = 0.6274
    koef = 0.0132
    Energy = koef * math.pow(Light, koef)
    return Energy

def GetResolution(Light):
    Energy = EnergyConv(Light)

    B = [14.29, 126, 81]
    Power = [1.5, 3.0]
    
    Resolution = math.sqrt(B[0] + B[1] * math.pow(Energy, Power[0]) + B[2] * math.pow(Energy, Power[1]))

    return  Resolution #percent