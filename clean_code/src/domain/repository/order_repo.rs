// interface adapter

#[allow(dead_code)]

use crate::domain::entity::order::Order;

pub trait OrderRepo {
    fn get_by_code(&self, code: &str) -> Option<Order>;
    fn save(&self, order: &mut Order, year: i32);
}
