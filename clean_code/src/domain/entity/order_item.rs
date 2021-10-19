// entity

#[allow(dead_code)]
use rust_decimal::prelude::*;

#[derive(Clone)]
pub struct OrderItem {
    pub item_id: u32,
    pub price: Decimal,
    pub quantity: i32,
}

impl OrderItem {
    pub fn subtotal(&self) -> Decimal {
        return self.price * Decimal::new(self.quantity.into(), 0);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use rust_decimal_macros::dec;

    #[test]
    fn shall_calculate_subtotal() {
        let order_item = OrderItem {
            item_id: 0,
            price: dec!(9.99),
            quantity: 3,
        };
        assert_eq!(order_item.subtotal(), dec!(29.97));
    }
}
