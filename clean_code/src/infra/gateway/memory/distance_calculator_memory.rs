#[allow(dead_code)]
use crate::domain::gateway::distance_calculator::DistanceCalculator;

pub struct DistanceCalculatorFake {}

impl DistanceCalculator for DistanceCalculatorFake {
  #[allow(unused_variables)]
  fn calculate(&self, origin: &str, destination: &str) -> u32 {
    return 1000;
  }
}

#[cfg(test)]
mod tests {
  use super::*;
  #[test]
  fn shall_calculate_distance_given_two_zipcodes() {
    let calculator = DistanceCalculatorFake {};
    let distance = calculator.calculate("11.111-11", "99.999-99");
    assert_eq!(1000, distance);
  }
}
