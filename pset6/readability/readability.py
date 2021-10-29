from cs50 import get_string

# Prompt user for text
text = get_string("Text: ")
while len(text) <= 0:
    text = get_string("Text: ")

# Count number of letters, words and sentences in text
letters = 0
words = 1
sentences = 0

for i in range(len(text)):
    if text[i] >= "A" and text[i] <= "Z" or text[i] >= "a" and text[i] <= "z":
        letters += 1
    elif text[i] == " ":
        words += 1
    elif text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

# Calculate average number of letters per 100 words - L
L = (letters / words) * 100

# Calculate average number of sentences per 100 words - S
S = (sentences / words) * 100

# Coleman-Liau
index = round(0.0588 * L - 0.296 * S - 15.8)

# Print grader-level
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")