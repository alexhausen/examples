#[allow(dead_code)]

// DTO (data transfer object)
pub struct PlaceOrderItemInput {
  pub id: u32,
  pub quantity: i32,
}

// DTO
pub struct PlaceOrderInput {
  pub cpf: String,
  pub zipcode: String,
  pub coupon_code: String,
  pub items: Vec<PlaceOrderItemInput>,
}
