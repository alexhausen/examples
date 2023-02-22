// https://google.github.io/comprehensive-rust/exercises/day-2/luhn.html

// TODO: remove this when you're done with your implementation.
#![allow(unused_variables, dead_code)]

pub fn luhn(cc_number: &str) -> bool {
    // Ignore all spaces.
    let numbers = cc_number
        .chars()
        .filter(|c| !c.is_whitespace())
        .collect::<Vec<_>>();
    // Digits only.
    if numbers.iter().any(|c| !c.is_digit(10)) {
        return false;
    }
    // Reject number with less than two digits.
    if numbers.len() < 2 {
        return false;
    }
    // Moving from right to left, double every second digit:
    // for the number 1234, we double 3 and 1.
    let processed_digits: Vec<u32> = numbers
        .iter()
        .rev()
        .enumerate()
        .map(|(i, c)| -> u32 {
            let digit = c.to_digit(10).unwrap();
            if i % 2 == 0 {
                return digit;
            } else {
                // After doubling a digit, sum the digits.
                // So doubling 7 becomes 14 which becomes 5.
                let doubled = digit * 2;
                let sum_digits = doubled / 10 + doubled % 10;
                sum_digits
            }
        })
        .collect();
    // Sum all the undoubled and doubled digits.
    let sum: u32 = processed_digits.iter().sum();
    // The credit card number is valid if the sum ends with 0.
    sum % 10 == 0
}

#[test]
fn test_non_digit_cc_number() {
    assert!(!luhn("foo"));
}

#[test]
fn test_empty_cc_number() {
    assert!(!luhn(""));
    assert!(!luhn(" "));
    assert!(!luhn("  "));
    assert!(!luhn("    "));
}

#[test]
fn test_single_digit_cc_number() {
    assert!(!luhn("0"));
}

#[test]
fn test_two_digit_cc_number() {
    assert!(luhn(" 0 0 "));
}

#[test]
fn test_valid_cc_number() {
    assert!(luhn("4263 9826 4026 9299"));
    assert!(luhn("4539 3195 0343 6467"));
    assert!(luhn("7992 7398 713"));
}

#[test]
fn test_invalid_cc_number() {
    assert!(!luhn("4223 9826 4026 9299"));
    assert!(!luhn("4539 3195 0343 6476"));
    assert!(!luhn("8273 1232 7352 0569"));
}

#[allow(dead_code)]
fn main() {}
