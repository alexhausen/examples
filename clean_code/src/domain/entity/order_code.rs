// value object
#[allow(dead_code)]
use std::str::FromStr;

#[derive(Clone, PartialEq)]
pub struct OrderCode {
    pub value: String,
}

impl OrderCode {
    pub fn new(year: i32, number: usize) -> OrderCode {
        let code = format!("{:04}{:08}", year, number);
        return OrderCode { value: code };
    }
}

impl FromStr for OrderCode {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        Ok(OrderCode {
            value: s.to_string(),
        })
        // TODO error handling
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn check_new_code() {
        let order_code = OrderCode::new(2021, 123);
        assert_eq!("202100000123", order_code.value);
    }

    #[test]
    fn check_code_from_str() {
        let order_code = OrderCode::from_str("202100000123").unwrap();
        assert_eq!("202100000123", order_code.value);
    }
}
