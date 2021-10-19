// interface adapter

#[allow(dead_code)]
use crate::domain::entity::coupon::Coupon;

pub trait CouponRepo {
    fn get_by_code(&self, code: &str) -> Option<Coupon>;
}

pub struct CouponRepoDatabase {}

impl CouponRepo for CouponRepoDatabase {
    fn get_by_code(&self, _code: &str) -> Option<Coupon> {
        // db.query!("select * from coupon where coupon.code = '{}'", code);
        return None;
    }
}
