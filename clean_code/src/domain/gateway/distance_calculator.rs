// gateway

#[allow(dead_code)]

pub trait DistanceCalculator {
    fn calculate(&self, origin: &str, destination: &str) -> u32;
}
