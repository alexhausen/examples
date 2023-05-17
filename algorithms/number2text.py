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

# remove empty spaces, False, None... from the list


def remove_falses(ls):
    return list(filter(lambda v: v, ls))


def convert_from_1_to_999(n):
    # 1 - 999
    values_str = []
    hundred = n // 100
    if hundred > 0:
        values_str.append(NUMBERS_1_TO_9[hundred])
        values_str.append("hundred")
        n %= 100
    if n < 20:
        values_str.append(NUMBERS_1_TO_19[n])
    else:
        tens = n % 100 // 10
        unit = n % 10
        values_str.append(TENS[tens])
        values_str.append(NUMBERS_1_TO_9[unit])
    return values_str


def number_to_text(arg):
    n = int(arg)
    # base case
    if n == 0:
        return "zero"
    values_str = []
    # num_pow_1000 = 0
    # temp = n // 1000
    # while temp > 0:
    #     temp //= 1000
    #     num_pow_1000 += 1
    num_pow_1000 = int(math.log(n, 1000))
    while num_pow_1000 >= 0:
        pow_1000 = pow(1000, num_pow_1000)
        part_1000 = n // pow_1000
        parts_str = convert_from_1_to_999(part_1000)
        parts_str = remove_falses(parts_str)
        if len(parts_str) != 0:
            parts_str.append(POWER_1000[num_pow_1000])
        values_str += parts_str
        n %= pow_1000
        num_pow_1000 -= 1
    values_str = remove_falses(values_str)
    return " ".join(values_str)


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
