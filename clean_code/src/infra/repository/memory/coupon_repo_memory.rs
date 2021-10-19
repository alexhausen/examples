#[allow(dead_code)]
use chrono::prelude::*;
use rust_decimal_macros::dec;
use crate::domain::entity::coupon::Coupon;
use crate::domain::repository::coupon_repo::CouponRepo;


pub struct CouponRepoFake {}

impl CouponRepoFake {
    fn coupons() -> Vec<Coupon> {
        return vec![
            Coupon {
                code: "VALE20".to_string(),
                percentage: dec!(20),
                expiration_date: Utc.ymd(2022, 12, 25),
            },
            Coupon {
                code: "VALE50".to_string(),
                percentage: dec!(50),
                expiration_date: Utc.ymd(2020, 1, 1),
            },
        ];
    }
}

impl CouponRepo for CouponRepoFake {
    fn get_by_code(&self, code: &str) -> Option<Coupon> {
        if let Some(coupon_ref) = CouponRepoFake::coupons()
            .iter()
            .find(|coupon| coupon.code.as_str() == code)
        {
            return Some(coupon_ref.clone());
        }
        return None;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn shall_find_coupon_by_code() {
        let repo: Box<dyn CouponRepo> = Box::new(CouponRepoFake {});
        let coupon_found = repo.get_by_code("VALE50");
        assert_eq!(coupon_found.is_some(), true);
        assert_eq!(coupon_found.unwrap().code, "VALE50");

        let coupon_found = repo.get_by_code("VALE100");
        assert_eq!(coupon_found.is_none(), true);
    }
}
