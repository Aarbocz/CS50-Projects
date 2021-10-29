from cs50 import get_float

# Prompt user for change owed
change = -1
while change < 0:
    change = get_float("Change owed: ")

# Transform dollar into cents
cents = round(int(change * 100))

# Calculate coins needed for change
coins = 0
while cents >= 25:
    cents -= 25
    coins += 1
while cents >= 10:
    cents -= 10
    coins += 1
while cents >= 5:
    cents -= 5
    coins += 1
while cents >= 1:
    cents -= 1
    coins += 1

# Print min amout of coins needed
print(coins)