import numpy as np
import math
from scipy.integrate import quad



#Gauss Func normalized by sigma
def Gauss(Ex, sigma):
    k = 1. / (sigma * math.sqrt(2*math.pi))
    s = -0.5 / (sigma * sigma)
    def f(x):
        return k * math.exp(s * (x - Ex)*(x - Ex))
    return f

#Func to Blur detector data by Gauss
def Blur(Hist, Resolution, bin_):

    N = len(Hist[0])

    #make Hist's copy
    HistBlur = np.array([np.copy(Hist[0]), np.zeros(N)])

    #get i bin in Hist 
    #calc contribution in HistBlur
    for i in range(0, N):
        bin_now = Hist[0][i]
        amount_now = Hist[1][i]


        if(amount_now > 0):
            #Resoution for Energy = bin_now
            Res = Resolution(bin_now)

            sigma = bin_now * Res / 2.35 #sigma for current Energy
            
            #find contribution's bin
            #99% in 3*sigma
            #number bins for blur by current step
            n = int(3. * sigma / bin_)

            if(n > 1):

                #min bin
                if(i - n < 0):
                    min_ = 0
                else:
                    min_ = i - n

                #max bin
                if(i + n > N):
                    max_ = N
                else:
                    max_ = i + n

                veckoef = []

                #blur_vec
                for m in range(min_, max_):
                    #calc sum of 3 points
                    x0 = m * bin_
                    x2 = (m + 1) * bin_
                    
                    f = quad(Gauss(bin_now, sigma), x0, x2)
                    
                    veckoef.append(f[0])
                
                #normalize vecKoef
                veckoef = np.array(veckoef)
                sum_ = np.sum(veckoef)
                veckoef /= sum_
                
                
                tmp = 0
                for indx in range(min_, max_):
                    HistBlur[1][indx] += veckoef[tmp] * amount_now
                    tmp += 1

                
            else:
                HistBlur[1][i] += amount_now

    return HistBlur
########################

#Func to Convert Array[read Geant data from .txt file] to Histogram
def ConvertToHist(Particles, bin_, N):
    
    Energy = []
    Amount = []
    
    tmp = 0
        
    for i in range(0, N):

        bin_now = (i + 0.5) * bin_#bin_now
        bin_next = (i + 1.) * bin_#maxs Energy of bin_now
        amount = 0

        #add Energy in Hist
        #tmp - index for all
        size_all = len(Particles)
        while((size_all - 1 > tmp)and(Particles[tmp] <= bin_next)):
            amount += 1 #add particle in column
            tmp += 1 #go to next particle
        
        #add bin
        Energy.append(bin_now)
        Amount.append(amount)
    Energy = np.array(Energy)
    Amount = np.array(Amount)

    #Hist = (np.array([Energy, Amount]))
    return np.array([Energy, Amount])
###################################################################

#Main function of Reader
def ReadAndConvert(str, Light, Resolution, bin_, N):
    #arrays for different partycles
    particles = []

    f = open(str, 'r')
    
    EnergyFull = 0
    
    PrevNeutronTime = 0.
    NowNeutronTime = 0.
    f.readline() #skip first line

    once = []
    twice = []
    multi = []
    i = 0
    for line in f:
        NeutronBornTime,  Type, Energy = line.split('\t')
        
        Energy = Light(float(Energy))
        NeutronBornTime = int(NeutronBornTime) #event
        Type = np.str_(Type) #name

        PrevNeutronTime = NowNeutronTime
        NowNeutronTime = NeutronBornTime


        #You can change particle that will be in Histogram
        if(PrevNeutronTime == NowNeutronTime):
            i += 1
            EnergyFull += Energy
        else:
            if(EnergyFull > Light(0.1)):#1 MeV
                if(i == 1):
                    once.append(EnergyFull)
                elif(i == 2):
                    twice.append(EnergyFull)
                else:
                    multi.append(EnergyFull)
                #particles.append(EnergyFull)
            i = 0
            EnergyFull = Energy
    
    f.close()
    
    particles = once
    particles.extend(twice)
    particles.extend(multi)
    particles.sort()
    Hist = ConvertToHist(particles, bin_, N)
    Hist = Blur(Hist, Resolution, bin_)
    return Hist
########################