f = open("input.txt", "r", newline="\n")

cards = [None] * 215
amount = [0] * 215

i = 0
for line in f:
    x = line.split(":")[1]
    y = x.split("|")
    winning = y[0].split(" ")
    while '' in winning:
        winning.remove('')
    have = y[1][:-1].split(" ")
    while '' in have:
        have.remove('')

    cards[i] = (winning, have)
    amount[i] = 1
    i += 1

for i in range(0, 215):
    if amount[i] == 0:
        continue

    matches = 0
    w = cards[i][0]
    h = cards[i][1]

    for j in w:
        if j in h:
            matches += 1

    for j in range(i+1, i+1+matches):
        amount[j] += amount[i]


print(sum(amount))
