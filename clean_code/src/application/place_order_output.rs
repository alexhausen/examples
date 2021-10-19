#[allow(dead_code)]
use rust_decimal::prelude::*;

// DTO
pub struct PlaceOrderOutput {
    pub total: Decimal,
    pub shipping: Decimal,
    pub code: String,
}
