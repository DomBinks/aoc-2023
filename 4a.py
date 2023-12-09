f = open("input.txt", "r", newline="\n")

total = 0

for line in f:
    matches = 0

    x = line.split(":")[1]
    y = x.split("|")
    winning = y[0].split(" ")
    while '' in winning:
        winning.remove('')
    have = y[1][:-1].split(" ")
    while '' in have:
        have.remove('')

    print(str(winning) + "|" + str(have))

    for i in winning:
        if i in have:
            matches += 1

    print("matches: " + str(matches))
    if matches > 0:
        total += (2 ** (matches-1))
    print("total: " + str(total))

print("\n" + str(total))
