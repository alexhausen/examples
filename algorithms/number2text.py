"""
Convert a number from 0 to 999_999_999_999 to text
"""

import math

NUMBERS_1_TO_9 = [
    "",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
]

NUMBERS_1_TO_19 = NUMBERS_1_TO_9 + [
    "ten",
    "eleven",
    "twelve",
    "thirteen",
    "fouteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen"
]

TENS = [
    "",
    "",
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety",
]

POWER_1000 = [
    "",
    "thousand",
    "million",
    "billion"
]


def convert_from_1_to_999(n):
    # 1 - 999
    n_str = ""
    hundred = n // 100
    if hundred > 0:
        n_str += NUMBERS_1_TO_9[hundred] + " hundred"
        n %= 100
    if n < 20:
        n_str += " " + NUMBERS_1_TO_19[n]
    else:
        tens = n % 100 // 10
        unit = n % 10
        n_str += " " + TENS[tens] + " "
        n_str += NUMBERS_1_TO_9[unit]
    n_str = n_str.strip()
    return n_str


def number_to_text(arg):
    n = int(arg)
    # base case
    if n == 0:
        return "zero"
    n_str = ""

    # num_pow_1000 = 0
    # temp = n // 1000
    # while temp > 0:
    #     temp //= 1000
    #     num_pow_1000 += 1
    num_pow_1000 = int(math.log(n, 1000))
    while num_pow_1000 >= 0:
        p = pow(1000, num_pow_1000)
        part = n // p
        part_str = convert_from_1_to_999(part)
        if part_str:
            n_str += part_str
            n_str += " " + POWER_1000[num_pow_1000]
        n_str = n_str.strip()
        n_str += " "
        n %= p
        num_pow_1000 -= 1
    return n_str.strip()


if __name__ == "__main__":
    assert number_to_text(0) == "zero"
    assert number_to_text(1) == "one"
    assert number_to_text(2) == "two"
    assert number_to_text(10) == "ten"
    assert number_to_text(20) == "twenty"
    assert number_to_text(42) == "forty two"
    assert number_to_text(111) == "one hundred eleven"
    assert number_to_text(560) == "five hundred sixty"
    assert number_to_text(1002) == "one thousand two"
    assert number_to_text(
        97_010_000_580) == "ninety seven billion ten million five hundred eighty"
