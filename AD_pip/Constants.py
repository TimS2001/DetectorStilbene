#const
#Energy_bins
BIN_L = 50 #light
MAX_L = 100e3 #light
MIN_L = 10 #light
BIN_E = 0.05 #MeV
MAX_E = 18.0 #MeV
MIN_E = 1.0 #MeV

EPS = 'f8'
ENERGY_ID = 0
LIGHT_ID = 0
AMOUNT_ID = 1
LEN = 4. #cm

B = 990
pw = 1.594

KOEF = 0.0 #const of Gauss filter

import numpy as np
EfHist = np.genfromtxt('sys_data/Carbon_cross_section.txt', dtype=[('E', '<f8'), ('S', '<f8')])

