import numpy as np
####################
    


#func of convertation
def ConvertToEnergy(Hist, EnergyConvertion, sizeBin_E, N):
    Hist = EnergyConvertion(Hist)
    
    bin = sizeBin_E
    MAX_E = bin * N

    NewHist = [np.linspace(0, MAX_E, N),np.zeros(N)]
    
    old = 0
    old_left_board = Hist[0][old]
    old_right_board = Hist[0][old + 1]

    new = 0
    new_left_board = NewHist[0][new]
    new_right_board = NewHist[0][new + 1]
    

    while(old < len(Hist[0]) - 2)and(old_left_board <= NewHist[0][N - 1]):
        old_left_board = Hist[0][old]
        old_right_board = Hist[0][old + 1]

        M = 1.
        new = 0
        new_left_board = NewHist[0][new]
        new_right_board = NewHist[0][new + 1]
        while(new < N - 2)and(new_right_board < old_left_board):
            new += 1
            new_left_board = NewHist[0][new]
            new_right_board = NewHist[0][new + 1]
        
        while(new < N - 2)and(new_left_board <= old_right_board):
            a = max(old_left_board, new_left_board)
            b = min(old_right_board, new_right_board)
            if(b > a):
                k = (b - a) / (old_right_board - old_left_board)
                M -= k

                NewHist[1][new] += k * Hist[1][old]
            new += 1
            new_left_board = NewHist[0][new]
            new_right_board = NewHist[0][new + 1]

        old += 1


    return NewHist