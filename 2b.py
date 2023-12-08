f = open("input.txt", "r", newline="\n")

total = 0

for line in f:
    gr = line.split(":")
    game = gr[0].split(" ")[1]
    rounds = gr[1].split(";")
    print(game)
    print(rounds)

    mr = 0
    mg = 0
    mb = 0

    valid = True
    for r in rounds:
        colors = r.split(",") 
        for c in colors:
            x = c.split(" ")[1:]
            amount = x[0] 
            color = x[1]
            if(color[-1:] == "\n"):
                color = color[:-1]
            
            if color == "red":
                mr = max(mr, int(amount))
            elif color == "green":
                mg = max(mg, int(amount))
            else:
                mb = max(mb, int(amount))

    if valid:
        print("valid")
        total += (mr * mg * mb)
    else:
        print("invalid")

print(str(total))
