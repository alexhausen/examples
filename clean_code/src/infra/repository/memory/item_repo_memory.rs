#[allow(dead_code)]
use crate::domain::entity::item::Item;
use crate::domain::repository::item_repo::ItemRepo;
use rust_decimal_macros::dec;

pub struct ItemRepoFake {}

impl ItemRepoFake {
    fn itens() -> Vec<Item> {
        return vec![
            Item {
                id: 1,
                description: "Guitarra".to_string(),
                price: dec!(1000),
                width: 100,
                height: 50,
                depth: 15,
                weight: dec!(3),
            },
            Item {
                id: 2,
                description: "Amplificador".to_string(),
                price: dec!(5000),
                width: 50,
                height: 50,
                depth: 50,
                weight: dec!(22),
            },
            Item {
                id: 3,
                description: "Cabo".to_string(),
                price: dec!(30),
                width: 10,
                height: 10,
                depth: 10,
                weight: dec!(1),
            },
        ];
    }
}

impl ItemRepo for ItemRepoFake {
    fn get_by_id(&self, id: u32) -> Option<Item> {
        if let Some(item_ref) = ItemRepoFake::itens().iter().find(|item| item.id == id) {
            return Some(item_ref.clone());
        }
        return None;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn shall_find_item_by_id() {
        let repo: Box<dyn ItemRepo> = Box::new(ItemRepoFake {});
        let item_found = repo.get_by_id(1);
        assert_eq!(item_found.is_some(), true);
        assert_eq!(item_found.unwrap().description.as_str(), "Guitarra");

        let item_found = repo.get_by_id(4);
        assert_eq!(item_found.is_none(), true);
    }
}
