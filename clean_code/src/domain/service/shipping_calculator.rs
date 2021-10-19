// interface adapter / domain service
#[allow(dead_code)]

use crate::domain::entity::item::Item;
use rust_decimal::prelude::*;
use rust_decimal_macros::dec;

pub struct ShippingCalculator {}

impl ShippingCalculator {
    pub fn calculate(distance: u32, item: &Item) -> Decimal {
        let dist = Decimal::new(distance.into(), 0);
        let cost = dist * item.volume() * item.density() / dec!(100);
        return if cost > dec!(10) { cost } else { dec!(10) };
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn shall_calculate_shipping_cost_for_an_item() {
        let item = Item {
            id: 1,
            description: "Amplificador".to_string(),
            price: dec!(5000),
            width: 50,
            height: 50,
            depth: 50,
            weight: dec!(22),
        };
        let distance: u32 = 1000;
        let shipping_cost = ShippingCalculator::calculate(distance, &item);
        assert_eq!(shipping_cost, dec!(220));
    }

    #[test]
    fn shall_have_minimun_shipping_cost() {
        let item = Item {
            id: 4,
            description: "Description".to_string(),
            price: dec!(30),
            width: 9,
            height: 9,
            depth: 9,
            weight: dec!(0.1),
        };
        let distance: u32 = 1000;
        let shipping_cost = ShippingCalculator::calculate(distance, &item);
        assert_eq!(shipping_cost, dec!(10));
    }
}
