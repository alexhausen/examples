// entity
#[allow(dead_code)]
use crate::domain::entity::coupon::Coupon;
use crate::domain::entity::cpf::CPF;
use crate::domain::entity::order_code::OrderCode;
use crate::domain::entity::order_item::OrderItem;
use chrono::prelude::*;
use rust_decimal::prelude::*;
use rust_decimal_macros::dec;

#[derive(Clone)]
pub struct Order {
    pub code: Option<OrderCode>,
    pub cpf: CPF,
    pub coupon: Option<Coupon>,
    pub items: Vec<OrderItem>,
    pub shipping: Decimal,
}

impl Order {
    pub fn new(cpf: &str) -> Result<Order, &str> {
        let cpf = CPF::new(cpf);
        if cpf.is_ok() {
            return Ok(Order {
                code: None,
                cpf: cpf.unwrap(),
                items: vec![],
                coupon: None,
                shipping: dec!(0),
            });
        }
        return Err(cpf.err().unwrap());
    }

    pub fn add_item(&mut self, id: u32, price: Decimal, quantity: i32) {
        let order_item = OrderItem {
            item_id: id,
            price: price,
            quantity: quantity,
        };
        self.items.push(order_item);
    }

    pub fn add_coupon(&mut self, coupon: Coupon, today: Date<Utc>) {
        if !coupon.expired(today) {
            self.coupon = Some(coupon);
        }
    }

    pub fn total(&self) -> Decimal {
        let mut sum = self
            .items
            .iter()
            .fold(dec!(0), |acc, item| acc + item.subtotal());
        if let Some(coupon) = &self.coupon {
            sum -= sum * coupon.percentage / dec!(100);
        }
        sum += self.shipping;
        return sum;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn shall_not_create_order_with_invalid_cpf() {
        let order = Order::new("111.111.111-11");
        assert_eq!(order.is_err(), true);
        assert_eq!(order.is_ok(), false);
    }

    #[test]
    fn shall_create_order_with_3_items() {
        let mut order = Order::new("864.464.227-84").unwrap();
        order.add_item(1, dec!(1000), 2);
        order.add_item(2, dec!(5000), 1);
        order.add_item(3, dec!(30), 3);
        assert_eq!(order.total(), dec!(7090));
    }

    #[test]
    fn shall_create_order_with_coupon() {
        let mut order = Order::new("864.464.227-84").unwrap();
        order.add_item(1, dec!(1000), 2);
        order.add_item(2, dec!(5000), 1);
        order.add_item(3, dec!(30), 3);
        order.add_coupon(
            Coupon {
                code: "VALE20".to_string(),
                percentage: dec!(20),
                expiration_date: Utc::today(),
            },
            Utc::today(),
        );
        assert_eq!(order.total(), dec!(5672));
    }

    #[test]
    fn shall_not_add_expired_coupon() {
        let mut order = Order::new("864.464.227-84").unwrap();
        order.add_item(1, dec!(1000), 2);
        order.add_item(2, dec!(5000), 1);
        order.add_item(3, dec!(30), 3);
        order.add_coupon(
            Coupon {
                code: "VALE20".to_string(),
                percentage: dec!(20),
                expiration_date: Utc.ymd(2020, 1, 1),
            },
            Utc.ymd(2021, 12, 31),
        );
        assert_eq!(order.total(), dec!(7090));
    }
}
