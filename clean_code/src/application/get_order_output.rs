#[allow(dead_code)]
use rust_decimal::prelude::*;

// DTO
pub struct GetOrderItemOutput {
    pub description: String,
    pub price: Decimal,
    pub quantity: i32,
}

pub struct GetOrderOutput {
    pub code: String,
    pub shipping: Decimal,
    pub total: Decimal,
    pub order_itens: Vec<GetOrderItemOutput>,
}
