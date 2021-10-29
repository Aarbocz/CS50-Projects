from cs50 import get_int

# Prompt user for height
height = 0
while height < 1 or height > 8:
    height = get_int("Height: ")

# Print pyramid
width = 0
for i in range(height):
    width += 1
    print(" " * (height - width), end="")
    print("#" * width, end="")
    print("  ", end="")
    print("#" * width, end="")
    print("")
    