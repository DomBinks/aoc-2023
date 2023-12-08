m = {"red": 12, "green": 13, "blue": 14}

f = open("input.txt", "r", newline="\n")

total = 0

for line in f:
    gr = line.split(":")
    game = gr[0].split(" ")[1]
    rounds = gr[1].split(";")
    print(game)
    print(rounds)

    valid = True
    for r in rounds:
        colors = r.split(",") 
        for c in colors:
            x = c.split(" ")[1:]
            amount = x[0] 
            color = x[1]
            if(color[-1:] == "\n"):
                color = color[:-1]
            
            if int(amount) > m[color]:
                valid = False

    if valid:
        print("valid")
        total += int(game)
    else:
        print("invalid")

print(str(total))
