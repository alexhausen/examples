#[allow(dead_code)]
use crate::domain::entity::cpf::CPF;
use crate::domain::entity::order::Order;
use crate::domain::entity::order_code::OrderCode;
use crate::domain::repository::order_repo::OrderRepo;
use rust_decimal_macros::dec;
use std::str::FromStr;


pub struct OrderRepoFake {}

static mut ORDER_TABLE: Vec<Order> = vec![];

impl OrderRepoFake {
    pub fn set_fake_data(&self) {
        unsafe {
            ORDER_TABLE = vec![Order {
                code: Some(OrderCode {
                    value: String::from("202000000005"),
                }),
                cpf: CPF {
                    value: "86446422784".to_string(),
                },
                coupon: None,
                items: vec![],
                shipping: dec!(10),
            }];
        }
    }

    pub fn reset_fake_data(&self) {
        unsafe {
            ORDER_TABLE = vec![];
        }
    }
}

impl OrderRepo for OrderRepoFake {
    fn get_by_code(&self, code: &str) -> Option<Order> {
        unsafe {
            if let Some(order_ref) = ORDER_TABLE.iter().find(|order| {
                if let Some(code_ref) = &order.code {
                    code_ref == &OrderCode::from_str(code).unwrap()
                } else {
                    false
                }
            }) {
                return Some(order_ref.clone());
            }
        }
        return None;
    }

    fn save(&self, order: &mut Order, year: i32) {
        unsafe {
            let id = ORDER_TABLE.len() + 1;
            let code = OrderCode::new(year, id);
            order.code = Some(code);
            ORDER_TABLE.push(order.clone());
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn shall_save_and_find_order_by_code() {
        let mut order = Order::new("864.464.227-84").unwrap();
        let order_repo_fake = OrderRepoFake {};
        order_repo_fake.reset_fake_data();
        let repo: Box<dyn OrderRepo> = Box::new(order_repo_fake);
        repo.save(&mut order, 2021);
        let order_found = repo.get_by_code("202100000001");
        assert_eq!(order_found.is_some(), true);
        assert_eq!(order_found.unwrap().cpf.value, "864.464.227-84");
    }
}
