import numpy as np
import math
from scipy.stats import chi2
from scipy.optimize import minimize
from scipy.integrate import quad

from AD_pip.AD_converter import GetResolution
from AD_pip.AD_converter import Gauss

from AD_pip.Constants import BIN_E, MAX_E, MIN_E, EPS, ENERGY_ID, AMOUNT_ID, LEN, KOEF, EfHist

#Функция для центарльной производной
def deriv(Hist):
    N = len(Hist[ENERGY_ID])
    Amount = []
    
    for i in range(0, N - 1):
        k = 0.
        if(Hist[ENERGY_ID][i] > MIN_E):
            dx = Hist[ENERGY_ID][i + 1] - Hist[ENERGY_ID][i - 1]
            dy = Hist[AMOUNT_ID][i + 1] - Hist[AMOUNT_ID][i - 1]
            k = dy/dx
        Amount.append(k)
    Amount.append(0.)
    return np.array([Hist[ENERGY_ID],Amount])


#Функция возращающая поправку на эффективность детектора для энергиия в МэВ
def GetEfEnergy(X, h):
    N = len(EfHist['E'])
    i = 1
    while((EfHist['E'][i] <= X)and(i < N - 1)):
        i += 1
    k = (EfHist['S'][i] - EfHist['S'][i - 1])/(EfHist['E'][i] - EfHist['E'][i - 1])
    b = EfHist['S'][i] - k * EfHist['E'][i]
    sig_C = k * X + b
    
    sig_H = 0.
    if(X <= 3.8):
        sig_H = 4.3 * math.pow(X, -0.58)
    elif(X <= 4.0):
        sig_H = -0.7720612 * X + 4.9162
    else:
        sig_H = 4.83 / math.sqrt(X) - 0.587

    k = sig_H / (sig_H + sig_C) * (1. - math.exp(- (sig_H + sig_C)* h))
    return  1./ k 

###############

#Функция - решение уравнения ГГ 2 рода
def RealDeriv(Hist):
    DHist = deriv(Hist)
    N = len(DHist[ENERGY_ID])
    
    for i in range(0, N):
        DHist[AMOUNT_ID][i] *= -1.0 * GetEfEnergy(DHist[ENERGY_ID][i], LEN)
    
    #DHist[AMOUNT_ID] *= -1.
    return DHist


#Функиця возращающая апроксимирующую гистограмму 
#Также возращает квадрат ошибки аппроксимации
def SquareErr(E, S, M, Hist):
    N = len(Hist[ENERGY_ID])
    bin_ = Hist[ENERGY_ID][1] - Hist[ENERGY_ID][0]
    AprAmount = []

    for m in range(0, N):
        x0 = Hist[ENERGY_ID][0] + (m - 0.5) * bin_
        x1 = Hist[ENERGY_ID][0] + (m + 0.5) * bin_
        tmp = quad(Gauss(E, S), x0, x1)
        AprAmount.append(tmp[0])
    AprHist = np.array([Hist[ENERGY_ID], AprAmount])
    IdealSum = np.sum(Hist[AMOUNT_ID])
    Sum = np.sum(AprHist[AMOUNT_ID])
    AprHist[AMOUNT_ID] *= M * IdealSum / Sum

    err = ((AprHist[AMOUNT_ID] - Hist[AMOUNT_ID]) ** 2)

    return AprHist, np.sum(err) / IdealSum / IdealSum

#Функция для МНК 
#Возвращает функция от трех переменных (e, s, M) f
#f - квадрат разности аппроксимации в точке (e, s, M) и данных
def Error(Hist):
    N = len(Hist[ENERGY_ID])
    bin_ = Hist[ENERGY_ID][1] - Hist[ENERGY_ID][0]
    
    def f(v): #(e, s, M)
        df = 0.
        AprAmount = []
        if(v[0] <= 0)or(v[1] <= 0)or(v[2] <= 0):
            return 1.e10

        for m in range(0, N):
            x0 = Hist[ENERGY_ID][0] + (m - 0.5) * bin_
            x1 = Hist[ENERGY_ID][0] + (m + 0.5) * bin_
            tmp = quad(Gauss(v[0], v[1]), x0, x1)
            AprAmount.append(tmp[0])
        AprHist = np.array([Hist[ENERGY_ID], AprAmount])        
        IdealSum = np.sum(Hist[AMOUNT_ID])
        Sum = np.sum(AprHist[AMOUNT_ID])
        AprHist[AMOUNT_ID] *= (v[2] * IdealSum / Sum)

        
        for m in range(0, N):
            filter_ = 1.
            if(KOEF != 0):
                filter_ = Gauss(v[0], v[1] * math.sqrt(KOEF))(Hist[ENERGY_ID][m])
            df += ((AprHist[AMOUNT_ID][m] - Hist[AMOUNT_ID][m]) ** 2) * filter_
        
        return df
    return f
        
#Функция по поиску пиков для данных 
def findPeaks(Hist):
    N = len(Hist[ENERGY_ID])

    DHist = deriv(Hist)
    
    peaks = []
    
    M = len(DHist[ENERGY_ID])
    for i in range(1, M - 1):
        if(DHist[AMOUNT_ID][i - 1] < 0)and(DHist[AMOUNT_ID][i + 1] > 0):
            peaks.append([DHist[ENERGY_ID][i], 'r'])#rise
        
        elif(DHist[AMOUNT_ID][i - 1] > 0)and(DHist[AMOUNT_ID][i + 1] < 0):
            peaks.append([DHist[ENERGY_ID][i], 'f'])#fall
    peaks.append([Hist[ENERGY_ID][N - 1],'n'])
    
    
    tmpHist = [[],[]]
    Peaks = []
    k = 0
    for i in range(0, N):
        while(peaks[k][1] != 'r')and(k < len(peaks) - 1):
            k += 1

        if(Hist[ENERGY_ID][i] > peaks[k][0]):
            Peaks.append(tmpHist)
            tmpHist = [[],[]]
            #print(peaks[k][0])
            k += 1
        else:
            tmpHist[ENERGY_ID].append(Hist[ENERGY_ID][i])
            tmpHist[AMOUNT_ID].append(Hist[AMOUNT_ID][i])
    Peaks.append(tmpHist)


    return Peaks 

#Функция возвращает мат ожидание, дисперсию и ошибку для пика на основе статистики
def getKoefStat(Peak):
    Ex0 = 0.
    Ex1 = 0.
    Ex2 = 0.

    N = len(Peak[ENERGY_ID])
    
    Ex0 = np.sum(Peak[AMOUNT_ID])

    if(Ex0 <= 0):
        return 0, 0, 0

    for i in range(0, N):
        Ex1 += Peak[1][i] * Peak[0][i]
        Ex2 += Peak[1][i] * (Peak[0][i] ** 2)
    
    #Normilize
    Ex1 /= Ex0
    Ex2 /= Ex0


    Dx = (Ex2 - Ex1 * Ex1)
    S = N/(N - 1) * Dx #square
    
    if(S <= 0):
        return 0, 0, 0
    #'''
    #err by Xi_2
    ep = 0.95
    q1 = chi2.ppf(ep * 0.5, N - 1)
    q2 = chi2.ppf(1 - ep * 0.5, N - 1)
    delSig = N * S * (1./q1 - 1./q2)
    err = delSig / S
    #'''
    return Ex1, math.sqrt(S), err ** 2
#####

#Функция возвращает мат ожидание, дисперсию и ошибку для пика на основе аппроксимации
def GetKoef(Hist):
    ex, s, err = getKoefStat(Hist)
    M = 1.
    
    v0 = np.array([ex, s, M])
    res = minimize(Error(Hist), v0)
    E = res.x[0]
    S = res.x[1]
    M = res.x[2]
    return E, S, M

#Функция производит анализ гистограммы 
#Также поиск пика, температуры, ошибки и характера реакции
def find(Hist):
    isDT = 1
    constDT = 13.316
    constDD = 28.531
    ################
    Peaks = findPeaks(Hist)
    numbDD = []
    numbDT = []
    for i in range(0, len(Peaks)):
        Peak = Peaks[i]
        E1, S1, err = getKoefStat(Peak)
        if((2.1 < E1 < 2.9)and(0. < constDD * constDD * S1 * S1 < 100.)):
            numbDD.append(i)
        elif((13.8 < E1 < 15.0)and(0. < constDT * constDT * S1 * S1 < 100.)):
            numbDT.append(i)
    
    MainPeak = [[],[]]
    if(len(numbDT) > 0):
        isDT = 1
        for numb in numbDT:
            MainPeak[0].extend(Peaks[numb][0])
            MainPeak[1].extend(Peaks[numb][1])
    elif(len(numbDD) > 0.):
        isDT = 0
        for numb in numbDD:
            MainPeak[0].extend(Peaks[numb][0])
            MainPeak[1].extend(Peaks[numb][1])
    else:
        print('NO PEAKS')
        return [[0],[0]], 0, 0, 0, -1


    E, S, M = GetKoef(MainPeak)
    AprHist, errGrad = SquareErr(E, S, M, MainPeak)
    tmp0, tmp1, errRand = getKoefStat(MainPeak)
    P = np.sum(MainPeak[AMOUNT_ID])
    errStat = 0.5 * (E / S) ** 2 / P


    RS = E * GetResolution(E) / 2.35
    S = math.sqrt((S * S - RS * RS)) * 1.0 #поправка для большей точности
    
    if(isDT == 1):
        T = (constDT * S) ** 2
    else:
        T = (constDD * S) ** 2
    
    err = math.sqrt(errGrad + errStat + errRand)
    dT = round(0.5 * err * 100)

    return AprHist, E, T, dT, isDT