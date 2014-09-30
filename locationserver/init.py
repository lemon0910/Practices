f = open("info", "w");
f.write(str(1024) + " " + str(5) + "\n")

for i in range(5):
    f.write(str(i) + " " + str(1000) + "\n")

num = 0
for i in range(1024):
    f.write(str(i) + " " + str(i) + " " + str(num) + "\n")
    num = (num + 1) % 5

f.close()

