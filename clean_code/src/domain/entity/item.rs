// entity

#[allow(dead_code)]
use rust_decimal::prelude::*;

#[derive(Clone)]
pub struct Item {
    pub id: u32,
    pub description: String,
    pub price: Decimal,
    pub width: u32,
    pub height: u32,
    pub depth: u32,
    pub weight: Decimal,
}

impl Item {
    pub fn volume(&self) -> Decimal {
        let width = Decimal::new(self.width.into(), 2);
        let height = Decimal::new(self.height.into(), 2);
        let depth = Decimal::new(self.depth.into(), 2);
        return width * height * depth;
    }

    pub fn density(&self) -> Decimal {
        return self.weight / self.volume();
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use rust_decimal_macros::dec;

    #[test]
    fn shall_compute_volume() {
        let item = Item {
            id: 1,
            description: "Amplificador".to_string(),
            price: dec!(5000),
            width: 50,
            height: 50,
            depth: 50,
            weight: dec!(22),
        };
        assert_eq!(item.volume(), dec!(0.125));
    }

    #[test]
    fn shall_compute_density() {
        let item = Item {
            id: 1,
            description: "Amplificador".to_string(),
            price: dec!(5000),
            width: 50,
            height: 50,
            depth: 50,
            weight: dec!(22),
        };
        assert_eq!(item.density(), dec!(176));
    }
}
