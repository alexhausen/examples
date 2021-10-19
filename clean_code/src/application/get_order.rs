// use case / application service
#[allow(dead_code)]
use crate::application::get_order_output::GetOrderItemOutput;
use crate::application::get_order_output::GetOrderOutput;
use crate::domain::repository::item_repo::ItemRepo;
use crate::domain::repository::order_repo::OrderRepo;
use rust_decimal_macros::dec;

pub struct GetOrder {
    order_repo: Box<dyn OrderRepo>,
    item_repo: Box<dyn ItemRepo>,
}

impl GetOrder {
    pub fn new(order_repo: Box<dyn OrderRepo>, item_repo: Box<dyn ItemRepo>) -> GetOrder {
        return GetOrder {
            order_repo,
            item_repo,
        };
    }

    pub fn execute(&self, input: &str) -> GetOrderOutput {
        let mut order_output = GetOrderOutput {
            code: "".to_string(),
            shipping: dec!(0),
            total: dec!(0),
            order_itens: vec![],
        };
        if let Some(order) = self.order_repo.get_by_code(input) {
            order_output.shipping = order.shipping;
            order_output.total = order.total();
            order_output.code = order.code.unwrap().value;
            for order_item in &order.items {
                if let Some(item) = self.item_repo.get_by_id(order_item.item_id) {
                    let order_item_output = GetOrderItemOutput {
                        description: item.description,
                        price: item.price,
                        quantity: order_item.quantity,
                    };
                    order_output.order_itens.push(order_item_output);
                }
            }
        }
        // TODO handle error: order not found
        return order_output;
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::infra::repository::memory::item_repo_memory::ItemRepoFake;
    use crate::infra::repository::memory::order_repo_memory::OrderRepoFake;

    #[test]
    fn shall_get_a_non_existing_order() {
        let item_repo_fake = Box::new(ItemRepoFake {});
        let order_repo_fake = Box::new(OrderRepoFake {});
        let get_order = GetOrder::new(order_repo_fake, item_repo_fake);
        let get_order_output = get_order.execute("202012345678");
        assert_eq!(get_order_output.code.as_str(), "");
    }

    #[test]
    fn shall_get_an_existing_order() {
        let item_repo_fake = Box::new(ItemRepoFake {});
        let order_repo_fake = Box::new(OrderRepoFake {});
        order_repo_fake.set_fake_data();
        let get_order = GetOrder::new(order_repo_fake, item_repo_fake);
        let get_order_output = get_order.execute("202000000005");
        assert_eq!(get_order_output.code.as_str(), "202000000005");
    }
}
