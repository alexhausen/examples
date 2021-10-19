// value object (DDD)

#[allow(dead_code)]
use regex::Regex;
use std::fmt;

#[derive(Clone)]
pub struct CPF {
    pub value: String,
}

impl CPF {
    pub fn new(cpf: &str) -> Result<CPF, &str> {
        if CPF::is_valid(cpf) {
            return Ok(CPF {
                value: cpf.to_string(),
            });
        }
        return Err("CPF Inválido");
    }

    fn is_valid(cpf: &str) -> bool {
        let clean_cpf = CPF::remove_punctuation(cpf);
        if !CPF::has_eleven_digits(clean_cpf.as_str()) {
            return false;
        }
        if CPF::are_all_digits_the_same(clean_cpf.as_str()) {
            return false;
        }
        let digit1 = CPF::compute_digit(&clean_cpf[0..9]);
        let digit2 = CPF::compute_digit(&clean_cpf[0..10]);
        return CPF::match_digits(digit1, digit2, clean_cpf.as_str());
    }

    fn match_digits(digit1: u32, digit2: u32, cpf: &str) -> bool {
        let cpf_digit1 = (cpf.as_bytes()[9] as char).to_digit(10).unwrap();
        let cpf_digit2 = (cpf.as_bytes()[10] as char).to_digit(10).unwrap();
        return digit1 == cpf_digit1 && digit2 == cpf_digit2;
    }

    fn compute_digit(part: &str) -> u32 {
        let mut digit: u32 = 0;
        let factor = part.len() + 1;
        for (i, c) in part.chars().enumerate() {
            let d = c.to_digit(10).unwrap();
            let temp = (factor - i) as u32;
            digit += d * temp;
        }
        let rest = digit % 11;
        digit = if rest < 2 { 0 } else { 11 - rest };
        return digit;
    }

    fn remove_punctuation(cpf: &str) -> String {
        let re = Regex::new("[\\.|/|\\-]").unwrap();
        let clean_cpf = re.replace_all(cpf, "");
        return String::from(clean_cpf);
    }

    fn are_all_digits_the_same(cpf: &str) -> bool {
        let first = cpf.chars().nth(0).unwrap();
        let result = cpf.chars().fold(true, |mut acc, c| {
            acc &= c == first;
            acc
        });
        return result;
    }

    fn has_eleven_digits(cpf: &str) -> bool {
        let re = Regex::new("^(\\d){11}$").unwrap();
        let result = re.is_match(cpf);
        return result;
    }
}

impl fmt::Display for CPF {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        // TODO format CPF output to string xxx.xxx.xxx-xx
        f.write_str(self.value.as_ref())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn valid_cpfs() {
        assert_eq!(CPF::is_valid("86446422784"), true);
        assert_eq!(CPF::is_valid("91720489726"), true);
        assert_eq!(CPF::is_valid("864.464.227-84"), true);
        assert_eq!(CPF::is_valid("111.444.777-35"), true);
    }

    #[test]
    fn invalid_cpfs() {
        assert_eq!(CPF::is_valid("00000000000"), false);
        assert_eq!(CPF::is_valid("111.111.111-11"), false);
        assert_eq!(CPF::is_valid("86446422799"), false);
        assert_eq!(CPF::is_valid("a1720489726"), false);
        assert_eq!(CPF::is_valid("86446422784a"), false);
    }
}
