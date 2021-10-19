// interface adapter

#[allow(dead_code)]
use crate::domain::entity::item::Item;

pub trait ItemRepo {
    fn get_by_id(&self, id: u32) -> Option<Item>;
}

pub struct ItemRepoDatabase {}

impl ItemRepo for ItemRepoDatabase {
    fn get_by_id(&self, _id: u32) -> Option<Item> {
        // db.query!("select * from item where id = {}", id);
        return None;
    }
}
