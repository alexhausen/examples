// entity

#[allow(dead_code)]
use chrono::prelude::*;
use rust_decimal::prelude::*;

#[derive(Clone)]
pub struct Coupon {
    pub code: String,
    pub percentage: Decimal,
    pub expiration_date: Date<Utc>,
}

impl Coupon {
    pub fn expired(&self, today: Date<Utc>) -> bool {
        return today > self.expiration_date;
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use rust_decimal_macros::dec;

    #[test]
    fn expired_coupons() {
        let coupon1 = Coupon {
            code: "code".to_string(),
            percentage: dec!(10),
            expiration_date: Utc.ymd(2019, 1, 1),
        };
        assert_eq!(coupon1.expired(Utc.ymd(2019, 1, 2)), true);
        let coupon2 = Coupon {
            code: "code".to_string(),
            percentage: dec!(10),
            expiration_date: Utc.ymd(2019, 1, 1),
        };
        assert_eq!(coupon2.expired(Utc.ymd(2020, 1, 1)), true);
    }

    #[test]
    fn valid_coupons() {
        let coupon1 = Coupon {
            code: "code".to_string(),
            percentage: dec!(10),
            expiration_date: Utc.ymd(2019, 1, 1),
        };
        assert_eq!(coupon1.expired(Utc.ymd(2019, 1, 1)), false);
        let coupon2 = Coupon {
            code: "code".to_string(),
            percentage: dec!(10),
            expiration_date: Utc.ymd(2020, 1, 1),
        };
        assert_eq!(coupon2.expired(Utc.ymd(2019, 1, 1)), false);
    }
}
