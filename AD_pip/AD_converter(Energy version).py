import numpy as np
from numpy import genfromtxt
import math
from scipy.integrate import quad

from AD_pip.Constants import BIN_E, MAX_E, MIN_E, EPS, ENERGY_ID, AMOUNT_ID, LEN



#adition func

#Функция гаусса нормированнная для ДИСПЕРСИИ
def Gauss(Ex, sigma):
    k = 1. / (sigma * math.sqrt(2*math.pi))
    s = -0.5 / (sigma * sigma)
    def f(x):
        return k * math.exp(s * (x - Ex)*(x - Ex))
    return f



#Функция для чтения гистограммы из файла str
def readHist(str):
    Hist = np.genfromtxt(str)
    return Hist

###############
#lineral's func 
#Функция возращающая разрешение детектора для конкретной энергии в МэВ
def GetResolution(X):
    if(X <= 0):
        return 0
        #exeption
    
    #L = 1.549 * (X ** 1.5)
    #Y = math.sqrt(14.29 + 195 / L + 1.35 / L / L) / 100
    
    Y = math.sqrt(14.29 + 126 / (X ** 1.5) + 81 / (X ** 3)) / 100
    return  Y



######################
#AD func

#func to blur by Gauss
#Функция размытия по гауссу
#Нужна чтобы учтиывать разрешающую способность детектора
def Blur(Hist):

    N = len(Hist[ENERGY_ID])

    #make Hist's copy
    HistBlur = np.array([Hist[ENERGY_ID], np.zeros(N)])

    #get i bin in Hist 
    #calc contribution in HistBlur
    for i in range(0, N):
        bin_now = Hist[ENERGY_ID][i]
        amount_now = Hist[AMOUNT_ID][i]


        if(amount_now > 0):
            #Resoution for Energy = bin_now
            Res = GetResolution(bin_now)

            sigma = bin_now * Res / 2.35 #sigma for current Energy
            
            #find contribution's bin
            #99% in 3*sigma
            #number bins for blur by current step
            n = int(3. * sigma / BIN_E)

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
                    x0 = m * BIN_E
                    x2 = (m + 1) * BIN_E
                    
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
    bin_ = BIN_E
    max_ = MAX_E
    N = int(max_ / bin_)
    
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
    Energy = np.array(Energy, EPS)
    Amount = np.array(Amount, EPS)
    Hist = Blur(np.array([Energy, Amount]))

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
    EnergyLocal = 0
    EnergyNow = 0.
    EnergyLast = 0.
    EnergyMax = 0.
    TimeNow = 0.
    TimeLast = 0.
    
    PrevNeutronTime = 0.
    NowNeutronTime = 0.
    f.readline()
    for line in f:
        Energy, ProtonBornTime, NeutronBornTime, Type = line.split('\t')
        Energy = float(Energy) #/ 1000. # MeV
        ProtonBornTime = float(ProtonBornTime) #ns
        NeutronBornTime = float(NeutronBornTime) #ns
        Type = np.str_(Type) #p/e
        PrevNeutronTime = NowNeutronTime
        NowNeutronTime = NeutronBornTime

        
    
        if(PrevNeutronTime == NowNeutronTime):
            interactions += 1
            EnergyLocal += Energy
        else:
            if(interactions == 1):
                once.append(EnergyLocal)
            elif(interactions == 2):
                twice.append(EnergyLocal)
            elif(interactions == 3):
                triple.append(EnergyLocal)
            else:
                multi.append(EnergyLocal)
            interactions = 1
            EnergyLocal = Energy
    
    f.close()
    
    #time = 0.1
    #print((once + twice) / 1000 / 1000 / time, ' * 10^6 событий / сек')
    
    
    #once.sort()
    #twice.sort()
    #triple.sort()
    #multi.sort()

    Particles = []
    for Energy in once:
        Particles.append(Energy)
    for Energy in twice:
        Particles.append(Energy)      
    for Energy in triple:
        Particles.append(Energy)    
    for Energy in multi:
        Particles.append(Energy)    

    Particles.sort()


    Hist = AddToHist(Particles)
    
    return Hist

#####################


#Функция для печати гистограммы в файл
def print1(Hist, str):
    N = len(Hist[0])
    with open(str, "w") as file:
        for i in range(0, N - 1):
            file.write(np.str_(Hist[0][i]))
            file.write("\t")
            file.write(np.str_(Hist[1][i]))
            file.write("\n")
