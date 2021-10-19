// use case / application service
#[allow(dead_code)]
use crate::application::place_order_input::*;
use crate::application::place_order_output::PlaceOrderOutput;
use crate::domain::entity::coupon::Coupon;
use crate::domain::entity::item::Item;
use crate::domain::entity::order::Order;
use crate::domain::factory::repository_factory::RepositoryFactory;
use crate::domain::gateway::distance_calculator::DistanceCalculator;
use crate::domain::repository::coupon_repo::CouponRepo;
use crate::domain::repository::item_repo::ItemRepo;
use crate::domain::repository::order_repo::OrderRepo;
use crate::domain::service::shipping_calculator::ShippingCalculator;
use chrono::prelude::*;
use rust_decimal::prelude::*;

// use case
pub struct PlaceOrder {
    distance_calculator: Box<dyn DistanceCalculator>,
    coupon_repo: Box<dyn CouponRepo>,
    item_repo: Box<dyn ItemRepo>,
    order_repo: Box<dyn OrderRepo>,
}

impl PlaceOrder {
    pub fn new(
        repo_factory: Box<dyn RepositoryFactory>,
        distance_calculator: Box<dyn DistanceCalculator>,
    ) -> PlaceOrder {
        return PlaceOrder {
            distance_calculator: distance_calculator,
            coupon_repo: repo_factory.create_coupon_repo(),
            item_repo: repo_factory.create_item_repo(),
            order_repo: repo_factory.create_order_repo(),
        };
    }

    fn find_coupon(&self, code: &str) -> Option<Coupon> {
        return self.coupon_repo.get_by_code(code);
    }

    fn find_item(&self, id: u32) -> Option<Item> {
        return self.item_repo.get_by_id(id);
    }

    pub fn execute(&mut self, input: PlaceOrderInput, today: Date<Utc>) -> PlaceOrderOutput {
        let mut order = Order::new(input.cpf.as_str()).unwrap(); // TODO handle error: invalid argument
        let distance = self
            .distance_calculator
            .calculate("99.999-99", input.zipcode.as_str());
        for item_input in &input.items {
            if let Some(item) = self.find_item(item_input.id) {
                order.add_item(item_input.id, item.price, item_input.quantity);
                let quantity = Decimal::new(item_input.quantity.into(), 0);
                order.shipping += ShippingCalculator::calculate(distance, &item) * quantity;
            }
            // TODO handle error: product not found
        }
        if let Some(coupon) = self.find_coupon(input.coupon_code.as_str()) {
            order.add_coupon(coupon, today);
        }
        let total = order.total();
        let shipping = order.shipping;
        self.order_repo.save(&mut order, today.year());
        return PlaceOrderOutput {
            total: total,
            shipping: shipping,
            code: order.code.unwrap().value.to_string(),
        };
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::infra::factory::memory::memory_repository_factory::MemoryRepositoryFactory;
    use crate::infra::gateway::memory::distance_calculator_memory::DistanceCalculatorFake;
    use rust_decimal_macros::dec;

    #[test]
    fn shall_place_order() {
        let repo_factory = Box::new(MemoryRepositoryFactory {});
        let distance_calculator_fake = Box::new(DistanceCalculatorFake {});
        let mut place_order = PlaceOrder::new(repo_factory, distance_calculator_fake);
        let input = PlaceOrderInput {
            cpf: "864.464.227-84".to_string(),
            zipcode: "11.111-11".to_string(),
            coupon_code: "VALE20".to_string(),
            items: vec![
                PlaceOrderItemInput { id: 1, quantity: 2 },
                PlaceOrderItemInput { id: 2, quantity: 1 },
                PlaceOrderItemInput { id: 3, quantity: 3 },
            ],
        };
        let output = place_order.execute(input, Utc::today());
        assert_eq!(output.total, dec!(5982.0));
    }

    #[test]
    fn shall_not_apply_expired_coupon() {
        let repo_factory = Box::new(MemoryRepositoryFactory {});
        let distance_calculator_fake = Box::new(DistanceCalculatorFake {});
        let mut place_order = PlaceOrder::new(repo_factory, distance_calculator_fake);
        let input = PlaceOrderInput {
            cpf: "864.464.227-84".to_string(),
            zipcode: "11.111-11".to_string(),
            coupon_code: "VALE50".to_string(),
            items: vec![PlaceOrderItemInput { id: 1, quantity: 2 }],
        };
        let output = place_order.execute(input, Utc::today());
        assert_eq!(output.total, dec!(2060.0));
    }

    #[test]
    fn shall_place_order_and_calculate_shipping() {
        let repo_factory = Box::new(MemoryRepositoryFactory {});
        let distance_calculator_fake = Box::new(DistanceCalculatorFake {});
        let mut place_order = PlaceOrder::new(repo_factory, distance_calculator_fake);
        let input = PlaceOrderInput {
            cpf: "864.464.227-84".to_string(),
            zipcode: "11.111-11".to_string(),
            coupon_code: "".to_string(),
            items: vec![
                PlaceOrderItemInput { id: 1, quantity: 2 },
                PlaceOrderItemInput { id: 2, quantity: 1 },
                PlaceOrderItemInput { id: 3, quantity: 3 },
            ],
        };
        let output = place_order.execute(input, Utc::today());
        assert_eq!(output.shipping, dec!(310));
    }
}
