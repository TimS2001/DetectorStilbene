#libraries
import math
##########

#constants
BIN_L = 1 #light
MAX_L =  800  #light
LEN = 4. #cm #Len of detector
##########
N = (int) (MAX_L / BIN_L)
#Energy into Light
def LightConv(Energy): #convert Energy[Mev] to Light
    A = 3.32e-3
    K = 1.448
    Light = A * math.pow(Energy * 1000, K)
    
    return Light
##################

#Light into Energy
def EnergyConv(Light):#[MeV]
    A = 51.35
    K = 0.69
    Energy = A * math.pow(Light, K)
    return Energy / 1000
##################

#Resolution in proportion
def GetResolution(Light):
    Energy = EnergyConv(Light)#this can be wrong, but I don`t know how change this step
    if(Energy == 0):
            return 0
    B = [14.29, 126, 81]
    Power = [-1.5, -3.0]
    
    Resolution = math.sqrt(B[0] + B[1] * math.pow(Energy, Power[0]) + B[2] * math.pow(Energy, Power[1])) #percentage
    return Resolution / 100 #proportion
#########################

