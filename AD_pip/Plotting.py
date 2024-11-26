import matplotlib.pyplot as plt


def plotHist(Hist):
    figure = plt.figure(figsize=(5, 5))#, dpi = 1000)        
    ax = figure.add_subplot()
    ax.plot(Hist[0], Hist[1])

    plt.show()
