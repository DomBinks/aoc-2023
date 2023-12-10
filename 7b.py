from collections import defaultdict
from functools import cmp_to_key

def compare(a, b):
    global tpe
    global strength

    if tpe[a] < tpe[b]:
        return -1
    elif tpe[a] > tpe[b]:
        return 1

    for i in range(0, len(a)):
        if strength[a[i]] < strength[b[i]]:
            return -1
        elif strength[a[i]] > strength[b[i]]:
            return 1

    return 0

f = open("input.txt", "r", newline="\n")

total = 0

strength = {'A': 14, 'K': 13, 'Q': 12, 'T': 10, '9': 9, '8': 8,
            '7': 7, '6': 6, '5': 5, '4':4, '3':3, '2':2, 'J':1}

bids = {} 
tpe = {}
jokers = defaultdict(lambda: 0)

for line in f:
    x = line.split(" ")
    hand = x[0]
    bid = int(x[1][:-1])
    bids[hand] = bid

    occur = defaultdict(lambda: 0)
    for i in hand:
        if i != 'J':
            occur[i] += 1
        else:
            jokers[hand] += 1

    vs = occur.values()

    if (5 in vs) or ((5-jokers[hand]) in vs) or (jokers[hand] == 5):
        tpe[hand] = 7

    elif (4 in vs) or (4-jokers[hand] in vs) or (jokers[hand] == 4):
        tpe[hand] = 6

    elif ((3 in vs) and (2 in vs)) or (list(vs).count(2) == 2 and jokers[hand] == 1) or \
         (jokers[hand] == 3 and (2 in vs)) or (jokers[hand] == 2 and (3 in vs)):
        tpe[hand] = 5

    elif (3 in vs) or (3-jokers[hand] in vs) or (jokers[hand] == 3):
        tpe[hand] = 4

    elif (list(vs).count(2) == 2) or ((2 in vs) and (jokers[hand] == 2)) or \
         (list(vs).count(1) >= 2 and jokers[hand] == 2):
        tpe[hand] = 3

    elif (2 in vs) or (2-jokers[hand] in vs) or (jokers[hand] == 2):
        tpe[hand] = 2

    else:
        tpe[hand] = 1

s = sorted(tpe.keys(), key=cmp_to_key(compare))

for i in range(0, len(s)):
    total += ((i+1) * bids[s[i]])

print(bids)
print(tpe)
print(s)

print("\n" + str(total))
