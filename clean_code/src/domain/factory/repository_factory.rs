// abstract factory
#[allow(dead_code)]
use crate::domain::repository::coupon_repo::CouponRepo;
use crate::domain::repository::item_repo::ItemRepo;
use crate::domain::repository::order_repo::OrderRepo;

pub trait RepositoryFactory {
    fn create_coupon_repo(&self) -> Box<dyn CouponRepo>;
    fn create_item_repo(&self) -> Box<dyn ItemRepo>;
    fn create_order_repo(&self) -> Box<dyn OrderRepo>;
}
