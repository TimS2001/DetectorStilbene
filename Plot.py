import AD_pip.AD_converter as conv
import AD_pip.Plotting as plot

str = 'data/detector_data.txt'   

Hist = conv.ReadAndBlur(str)
#plot.plotHist(Hist, 'MySpect')
plot.plotAndFind(Hist, 'MySpect')
