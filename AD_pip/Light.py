import math
import numpy as np
from scipy.integrate import quad

from AD_pip.Constants import LIGHT_ID, AMOUNT_ID, LEN, BIN_L, MAX_L, MIN_L, B, kk

def ConvLight(E):
    return B * (E ** kk)

def underE(L):
    return 0.0128 * (L ** 0.631)

def GetResolution(X):
    if(X <= 0):
        return 0
        #exeption
    
    A = 87000
    B = 38600000
    Y = math.sqrt(14.29 + A / (X ** 0.947) + B / (X ** 1.893) ) / 100
    return  Y

#Функция гаусса нормированнная для ДИСПЕРСИИ
def Gauss(Ex, sigma):
    k = 1. / (sigma * math.sqrt(2*math.pi))
    s = -0.5 / (sigma * sigma)
    def f(x):
        return k * math.exp(s * (x - Ex)*(x - Ex))
    return f

#Функция размытия по гауссу
#Нужна чтобы учтиывать разрешающую способность детектора
def Blur(Hist):

    N = len(Hist[LIGHT_ID])

    #make Hist's copy
    HistBlur = np.array([Hist[LIGHT_ID], np.zeros(N)])

    #get i bin in Hist 
    #calc contribution in HistBlur
    for i in range(0, N):
        bin_now = Hist[LIGHT_ID][i]
        amount_now = Hist[AMOUNT_ID][i]


        if(amount_now > 0):
            #Resoution for Energy = bin_now
            Res = GetResolution(bin_now)

            sigma = bin_now * Res / 2.35 #sigma for current Energy
            
            #find contribution's bin
            #99% in 3*sigma
            #number bins for blur by current step
            n = int(3. * sigma / BIN_L)

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
                    x0 = m * BIN_L
                    x2 = (m + 1) * BIN_L
                    
                    f = quad(Gauss(bin_now, sigma), x0, x2)
                    
                    veckoef.append(f[0])
                
                #normalize vecKoef
                veckoef = np.array(veckoef)
                sum_ = np.sum(veckoef)
                veckoef /= sum_
                
                
                tmp = 0
                for indx in range(min_, max_):
                    HistBlur[AMOUNT_ID][indx] += veckoef[tmp] * amount_now
                    tmp += 1

                
            else:
                HistBlur[AMOUNT_ID][i] += amount_now

    return HistBlur

#Функция преобразования данных по энергии частиц в гистограмму
def AddToHist(Particles):
    bin_ = BIN_L
    max_ = MAX_L
    N = int(max_ / bin_)
    
    Light = []
    Amount = []
    
    tmp = 0
        
    for i in range(0, N):

        bin_now = (i + 0.5) * bin_#bin_now
        bin_next = (i + 1.) * bin_#maxs Light of bin_now
        amount = 0

        #add Light in Hist
        #tmp - index for all
        size_all = len(Particles)
        while((size_all - 1 > tmp)and(Particles[tmp] <= bin_next)):
            amount += 1 #add particle in column
            tmp += 1 #go to next particle
        
        #add bin
        Light.append(bin_now)
        Amount.append(amount)
    Light = np.array(Light)
    Amount = np.array(Amount)
    i = 0 
    while(Light[i] < MIN_L):
        Amount[i] = 0
        i += 1

    Hist = Blur(np.array([Light, Amount]))

    

    return Hist


#Основная функция считывающая данные из файла
#Далее происходит Аналогово-Цифорвое преобразование данные в гистограмму с заданным разрешением детектора
def ReadAndBlur(str):
    once = []
    twice = []
    triple = []
    multi = []

    f = open(str, 'r')
    
    interactions = 1 
    LightLocal = 0
    
    PrevNeutronTime = 0.
    NowNeutronTime = 0.
    f.readline()
    for line in f:
        Energy, ProtonBornTime, NeutronBornTime, Type = line.split('\t')
        Light = ConvLight(float(Energy)) #/ 1000. # MeV
        ProtonBornTime = float(ProtonBornTime) #ns
        NeutronBornTime = float(NeutronBornTime) #ns
        Type = np.str_(Type) #p/e
        PrevNeutronTime = NowNeutronTime
        NowNeutronTime = NeutronBornTime

        
    
        if(PrevNeutronTime == NowNeutronTime):
            interactions += 1
            LightLocal += Light
        else:
            if(interactions == 1):
                once.append(LightLocal)
            elif(interactions == 2):
                twice.append(LightLocal)
            elif(interactions == 3):
                triple.append(LightLocal)
            else:
                multi.append(LightLocal)
            interactions = 1
            LightLocal = Light
    
    f.close()
    
    #time = 0.1
    #print((once + twice) / 1000 / 1000 / time, ' * 10^6 событий / сек')
    
    
    #once.sort()
    #twice.sort()
    #triple.sort()
    #multi.sort()

    Particles = []
    for Light in once:
        Particles.append(Light)
    for Light in twice:
        Particles.append(Light)      
    for Light in triple:
        Particles.append(Light)    
    for Light in multi:
        Particles.append(Light)    

    Particles.sort()


    Hist = AddToHist(Particles)
    
    return Hist
