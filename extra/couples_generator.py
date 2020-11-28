import time

def is_couple_exists(l:list, ab:tuple):
    for c in l:
        if c[0]==ab[1] and c[1]==ab[0]:
            return True
    return False

if __name__ == "__main__":
    numbers = [256, 1024, 4096, 16384, 65536, 262144, 1048576]
    coef = [6, 8, 10, 12, 14, 16, 18]
    output = dict()
    
    for i, n in enumerate(numbers):
        n_list = []
        start = time.time()
        result = list(map(lambda x: 2 ** x, range(coef[i])))

        for a in range(2, coef[i]):
            for b in range(2, coef[i]):
                if result[a] * result[b] == n and not is_couple_exists(n_list, (result[a], result[b])):
                    n_list.append((result[a], result[b]))
        output[n] = n_list
        end = time.time()
        print(f'~work time for {n} is {end-start} seconds.\n')

    with open('variations.txt', 'w') as f:
        for k, v in output.items():
            f.write(f'{k}\n')
            for x in v:
                f.write(f'\t{x}\n')
            f.write('*'*10)
            f.write('\n')
        print('file has been written successfully!')
