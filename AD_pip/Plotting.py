import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib
import pandas as pd
from AD_pip.Analysis import find, RealDeriv

def plotAndFind(Hist, str):
    isDT = 1
    MaxY = 15000.

    #############################
    Energy = Hist
    DEnergy = RealDeriv(Hist)#deriv(Energy)

    figure = plt.figure(figsize=(5, 5))#, dpi = 1000)
    k2 = 0.8 #1.0
    
    #'''
    ApprHist, E, T, dT, isDT = find(DEnergy)
    str1 = 'E$_{n}$ = ' + "{:.2f}".format(E) + ' MeV\nT$_{ion}$ = ' + "{:.1f}".format(T) + ' keV +- ' + "{:.0f}".format(dT) + '%'
    
    MaxY = 1.5 * np.max(ApprHist[1])
   
    for i in range(0, len(ApprHist[0])):
        ApprHist[1][i] *= k2
    
    #'''
    #############################
    
    for m in range(0, len(DEnergy[0])):
        DEnergy[1][m] *= k2
    
        
    ax = figure.add_subplot()
    ax.plot(Energy[0], Energy[1],  '.' ,markersize=4,label = 'Response', color = 'tab:blue') #), label = 'Отклик', color = 'tab:blue')#lightblue
    ax.plot(DEnergy[0], DEnergy[1], markersize=4,label = 'Derivative response', color = 'navy', alpha = 0.8)#, label = 'Производная', color = 'navy')
    ax.plot(ApprHist[0], ApprHist[1], markersize=4, label = 'Restored ' + str1, color = 'r', alpha = 0.5)
    #############################
   
   

    max2 = 16.5
    min2 = 0.1
    if(isDT == 0):
        max2 = 4. 
    ax.set_ylim(0, MaxY)
    
    ax.set_ylabel('Counts', fontsize = 12)
    ax.set_xlabel('Energy, MeV', fontsize=12)
    ax.xaxis.set_major_formatter(matplotlib.ticker.FormatStrFormatter('%.1f'))
    ax.set_xlim(min2, max2)
    ax.grid(which='major')
    ax.set_title(str, fontsize=12)
    matplotlib.rc('font', size=12)
    plt.legend(loc = 'upper right')
    #figure.savefig('pictures/' + str + '.png', bbox_inches='tight', pad_inches=0, dpi=1000)
    plt.show()

    return E, T, dT
#################################

def plotHist(Hist, str):
    Energy = Hist
    DEnergy = RealDeriv(Hist)#deriv(Energy)

    figure = plt.figure(figsize=(5, 5))#, dpi = 1000)
    k2 = 0.8 #1.0

    

    for m in range(0, len(DEnergy[0])):
        DEnergy[1][m] *= k2

        
    ax = figure.add_subplot()
    ax.plot(Energy[0], Energy[1],  '.' ,markersize=4,label = 'Response', color = 'tab:blue') #), label = 'Отклик', color = 'tab:blue')#lightblue
    ax.plot(DEnergy[0], DEnergy[1], markersize=4,label = 'Derivative response', color = 'navy', alpha = 0.8)#, label = 'Производная', color = 'navy')
    #############################



    max2 = 16.5
    min2 = 0.1

    ax.set_ylim(0, 2500)#2 * np.max(DEnergy))

    ax.set_ylabel('Counts', fontsize = 12)
    ax.set_xlabel('Energy, MeV', fontsize=12)
    ax.xaxis.set_major_formatter(matplotlib.ticker.FormatStrFormatter('%.1f'))
    ax.set_xlim(min2, max2)
    ax.grid(which='major')
    ax.set_title(str, fontsize=12)
    matplotlib.rc('font', size=12)
    plt.legend(loc = 'upper right')

    plt.show()