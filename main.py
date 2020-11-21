import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
import numpy as np
import csv
# import pandas


class TestPlot:
    def __init__(self, n, k, nk):
        self.n = n
        self.k = k
        self.nk = nk
        self.threads = []
        self.generating_performances = []
        self.sorting_performances = []
        self.total_performances = []

    def add_data(self, threads, generating_performance, sorting_performance, total_performance):
        self.threads.append(threads)
        self.generating_performances.append(generating_performance)
        self.sorting_performances.append(sorting_performance)
        self.total_performances.append(total_performance)
    
    def __repr__(self):
        return f"{self.nk}"


testplots_list = [] # a list of all TestPlot objects
plots_for_each_test = 6 # to group each 6 tests 2gether (same test, diff threads count)


def label_threads(threads):
    labels = []
    for th in threads:
        if th == 1:
            labels.append('One Threaded')
        else:
            labels.append(f'{th} Threads')

    return labels


def draw_plot(plot:TestPlot, filename):
    fig, ax1 = plt.subplots(figsize=(10, 4))
    # fig, ax1 = plt.subplots()

    threads = np.arange(len(plot.threads))
    print(plot.generating_performances)
    generating_rects = ax1.barh(threads, plot.generating_performances, align='center', height=0.33, tick_label=label_threads(plot.threads), label='Generating')
    sorting_rects = ax1.barh(threads+0.33, plot.sorting_performances, align='center', height=0.33, tick_label=label_threads(plot.threads), label='Sorting')
    total_rects = ax1.barh(threads+0.66, plot.total_performances, align='center', height=0.33, tick_label=label_threads(plot.threads), label='Total')

    ax1.set_title(f'Performance Test for:\nN={plot.n}, K={plot.k}, NxK={plot.nk}')

    ax1.xaxis.set_major_locator(MaxNLocator(11))
    ax1.xaxis.grid(True, linestyle='--', which='major', color='grey', alpha=.25)
    
    ax1.set_xlabel('Performance Time Measure (seconds)')

    max_width = max([r.get_width() for r in total_rects])
    for rect in total_rects:
        width = float(rect.get_width())
        performanceStr = '{:.4f}s'.format(width)
        if width >= max_width-max_width/4:
            xloc = -5
            clr = 'white'
            align = 'right'
        else:
            xloc = 5
            clr = 'black'
            align = 'left'
        yloc = rect.get_y() + rect.get_height() / 2
        label = ax1.annotate(performanceStr, xy=(width, yloc), xytext=(xloc, 0),
                            textcoords='offset points',
                            ha=align, va='center',
                            color=clr, weight='bold', clip_on=True)

    ax1.legend()
    plt.savefig(f'plots/{filename}.png')


if __name__ == "__main__":
    with open('test.csv', 'r') as csvfile:
        plots_data = csv.reader(csvfile, delimiter=',')
        tp = None
        for (index, row) in enumerate(plots_data, start=1):
            if tp == None:
                n = int(row[1])
                k = int(row[2])
                nk = int(row[3])
                tp = TestPlot(n, k, nk)

            threads = int(row[4])
            generating_performance = float(row[5])
            print(generating_performance)
            sorting_performance = float(row[6])
            total_performance = float(row[7])
            tp.add_data(threads, generating_performance, sorting_performance, total_performance)

            if index % plots_for_each_test == 0:
                testplots_list.append(tp)
                tp = None

    for i, testplot in enumerate(testplots_list, start=1):
        draw_plot(testplot, f'{testplot.nk} - {i}')
