def perm(n):
    if n == 1:
        return ['R', 'D']
    return ["".join([x, y]) for x in perm(n - 1) for y in perm(1)]
