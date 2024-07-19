import math

BIN_L = 1 #light
MAX_L = 1000  #light
MIN_L = 20 #light

def LightConv(Energy):
    k = [0.231, 0.3, 0.49097, 1.88055]
    Light = k[0] * Energy - k[1] * (1.0 - math.exp(- k[2] * math.pow(Energy, k[3])))
    return Light * 1000

def EnergyConv(Light):
    power = 0.7009
    koef = 0.02547
    Energy = koef * math.pow(Light, power)
    return Energy


#doesn't work
def GetResolution(Light):
    Energy = EnergyConv(Light)

    B = [14.29, 126, 81]
    Power = [1.5, 3.0]
    
    Resolution = math.sqrt(B[0] + B[1] * math.pow(Energy, Power[0]) + B[2] * math.pow(Energy, Power[1]))
    Resolution = 0
    return Resolution #percent