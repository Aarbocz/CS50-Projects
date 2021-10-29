from cs50 import get_int


def main():
    # Prompt user for credit card number
    credit_card_number = 0
    while credit_card_number <= 0:
        credit_card_number = get_int("Number: ")

    # Checks if conditions are met
    if check_validity(credit_card_number):
        print_credit_card_brand(credit_card_number)
    else:
        print("INVALID")

# Bool - Check if length and Luhn's algorithm are true


def check_validity(CCN):
    length = find_length(CCN)
    if length == 13 or length == 15 or length == 16 and checksum(CCN):
        return True
    else:
        return False

# Int - Finds out the length of the card


def find_length(CCN):
    length = 0
    while CCN >= 1:
        length += 1
        CCN /= 10
    return length

# Bool - Calculate Luhn's algorithm


def checksum(CCN):
    digit_sum = 0

    for i in range(find_length(CCN)):
        if (i % 2 == 0):
            digit_sum += CCN % 10
        else:
            digit = 2 * (CCN % 10)
            digit_sum += int(digit / 10) + (digit % 10)
        # Takes off last digit of CCN
        CCN -= CCN % 10
        CCN /= 10

    if (digit_sum % 10) == 0:
        return True
    else:
        return False

# Void - Prints the card brand


def print_credit_card_brand(CCN):
    if CCN >= 34e13 and CCN < 35e13 or CCN >= 37e13 and CCN <= 38e13:
        print("AMEX")
    elif CCN >= 51e14 and CCN < 56e14:
        print("MASTERCARD")
    elif CCN >= 4e12 and CCN < 5e12 or CCN >= 4e15 and CCN < 5e15:
        print("VISA")
    else:
        print("INVALID")


main()
