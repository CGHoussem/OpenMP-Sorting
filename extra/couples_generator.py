import time

# This was created to prevent doubles
def is_couple_exists(l:list, ab:tuple):
    for c in l:
        if c[0]==ab[1] and c[1]==ab[0]:
            return True
    return False

max_numbers = 10

if __name__ == "__main__":

    # generate numbers and coefs lists
    numbers = []
    coef = []
    i = 10
    while len(numbers) < max_numbers:
        numbers.append(2**i)
        coef.append(i)
        i += 2

    # generate variantes of n & k
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

    # create a file and dump the generated values in there
    with open('variations.txt', 'w') as f:
        for k, v in output.items():
            f.write(f'{k}\n')
            for x in v:
                f.write(f'\t{x}\n')
            f.write('*'*10)
            f.write('\n')
        print('file has been written successfully!')
