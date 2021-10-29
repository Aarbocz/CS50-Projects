from sys import argv
import csv

# Error message - incorret number of command-line arguments


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Open CSV file and read it into dictionary
    with open(argv[1], 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        dict_list = list(reader)

    # Open DNA sequence and read it as list
    with open(argv[2], 'r') as file:
        dna_sequence = file.read()

    # Get max value for each STR using dna_repeat
    STR_max = []
    for i in range(1, len(reader.fieldnames)):
        STR = reader.fieldnames[i]
        STR_max.append(dna_repeat(dna_sequence, STR))

    # Compare max str values to each person using check_max
    check_match(STR_max, dict_list, reader)


# Compute longest run of consectuvie repeats for each STR in the DNA sequence
def dna_repeat(dna_sequence, STR):
    STR_count = 0
    repetition = []
    STR_length = len(STR)
    i = 0
    while i < len(dna_sequence):
        if dna_sequence[i:i+STR_length] == STR:
            STR_count += 1
            i += STR_length
        else:
            i += 1
            repetition.append(STR_count)
            STR_count = 0

    return(max(repetition))


# Compare the Str counts against each row in the CSV file
def check_match(STR_max, dict_list, reader):
    x = []
    str_length = len(reader.fieldnames)
    for i in range(len(dict_list)):
        for j in range(1, str_length):
            x.append(dict_list[i][reader.fieldnames[j]])

    # Transform x into integers
    for i in range(len(x)):
        x[i] = int(x[i])

    count = 0
    # If longest run matches an individual, print individual
    for l in range(0, len(x), str_length - 1):
        if STR_max == x[l:l+str_length - 1]:
            print(dict_list[count]['name'])
            return
        count += 1

    # Else print "No match"
    print("No match")


main()
