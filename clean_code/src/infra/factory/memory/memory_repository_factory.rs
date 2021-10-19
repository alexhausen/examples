#[allow(dead_code)]
use crate::domain::factory::repository_factory::RepositoryFactory;
use crate::domain::repository::coupon_repo::CouponRepo;
use crate::domain::repository::item_repo::ItemRepo;
use crate::domain::repository::order_repo::OrderRepo;
use crate::infra::repository::memory::coupon_repo_memory::CouponRepoFake;
use crate::infra::repository::memory::item_repo_memory::ItemRepoFake;
use crate::infra::repository::memory::order_repo_memory::OrderRepoFake;

pub struct MemoryRepositoryFactory {}

impl RepositoryFactory for MemoryRepositoryFactory {
    fn create_coupon_repo(&self) -> Box<dyn CouponRepo> {
        return Box::new(CouponRepoFake {});
    }

    fn create_item_repo(&self) -> std::boxed::Box<(dyn ItemRepo)> {
        return Box::new(ItemRepoFake {});
    }

    fn create_order_repo(&self) -> std::boxed::Box<(dyn OrderRepo)> {
        return Box::new(OrderRepoFake {});
    }
}
