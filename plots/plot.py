from tkinter import Tk
from tkinter.filedialog import askopenfilename

import matplotlib.pyplot as plt
import numpy as np
import csv

from collections import defaultdict

from scipy.interpolate import make_interp_spline, BSpline

""" Global Performance dictionnary structure (G_Perf)
    {
        'NxK 1': {
            (N, K): NK_Perf, # variation 1 (N < K)
            (N, K): NK_Perf, # variation 2 (N = K)
            (N, K): NK_Perf, # variation 3 (N > K)
        },
        'NxK 2': }
            (N, K): NK_Perf, 
            (N, K): NK_Perf,
            (N, K): NK_Perf,
        },
        ...
    }
"""

""" NK Performance dictionnary structure (NK_Perf)
    {
        'Performance': [],
        // I can add other measures like generating performance, etc..
    }
"""

THREADS_ARR = np.array(['1', '2', '4', '8'])

def draw_bars(n:int, k:int, nk:int, nk_perf:defaultdict):
    measure = 's'

    m = max(nk_perf['Performance']) 
    if m >= 120:
        nk_perf['Performance'] = [x/60 for x in nk_perf['Performance']]
        measure = 'min'
    elif m < 1:
        nk_perf['Performance'] = [x*1000 for x in nk_perf['Performance']]
        measure = 'ms'

    rects = plt.bar(THREADS_ARR, nk_perf['Performance'], label='Performance')

    # for each rect annotate the performance attained
    for i, rect in enumerate(rects):
        x, y = rect.xy
        h = rect.get_height()
        plt.annotate('%.2f %s' % (nk_perf['Performance'][i], measure), (x, h)) 

    plt.grid()
    plt.xlabel('Threads')
    plt.ylabel(f'Performance ({measure})')
    nk_cmp = 'N = K'
    if n < k:
        nk_cmp = 'N < K'
    elif n > k:
        nk_cmp = 'N > K'
    
    plt.title(f'N = {n} K = {k}  ({nk_cmp})\nNK = {nk}')
    
    filename = f'bars/{nk} - ({n},{k}).jpg'
    plt.figlegend()
    plt.savefig(filename)
    plt.clf()
    print(f'plot saved to {filename}')

if __name__ == "__main__":
    
    Tk().withdraw()
    filename = askopenfilename()

    g_perf = dict()
    
    nk_var_counter = 0 # --> len(THREADS_ARR)
    nk_counter = 0 # --> 3 * len(THREADS_ARR)

    with open(filename, 'r') as csvfile:
        data = csv.DictReader(csvfile, delimiter=',')
        for row in data:
            nk_var_counter += 1
            nk_counter += 1
    
            nk = int(row['NxK'])
            n = int(row['N'])
            k = int(row['K'])

            if nk_counter == 1:
                g_perf[nk] = dict()
                nk_var = dict()

            if nk_var_counter == 1:
                nk_perf = defaultdict(list)

            nk_perf['Performance'].append(float(row['Performance']))
            
            if nk_var_counter == len(THREADS_ARR):
                nk_var_counter = 0
                nk_var[(n, k)] = nk_perf
            
            if len(nk_var) == 3:
                g_perf[nk] = nk_var
                
            if nk_counter == 3 * len(THREADS_ARR):
                nk_counter = 0


    for nk, g_perf_v in g_perf.items():
        for nk_var, nk_perf in g_perf_v.items():
            (n , k) = nk_var
            draw_bars(n, k, nk, nk_perf)
