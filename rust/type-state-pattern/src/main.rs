// https://www.youtube.com/watch?v=_ccDqRTx-JU

#![allow(unused)]

use std::collections::HashMap;

struct Locked;
struct Unlocked;

struct PasswordManager<State = Locked> {
    master_pass: String,
    passwords: HashMap<String, String>,
    // state: std::marker::PhantomData<State>,
    state: State
}

impl PasswordManager {
    pub fn new(master_pass: String) -> Self {
        PasswordManager {
            master_pass,
            passwords: Default::default(),
            state: Locked,
        }
    }
}

impl<State> PasswordManager<State> {
    pub fn encryption(&self) -> String {
        todo!()
    }

    pub fn version(&self) -> String {
        todo!()
    }
}

impl PasswordManager<Locked> {
    pub fn unlock(self, master_pass: String) -> PasswordManager<Unlocked> {
        PasswordManager {
            master_pass: self.master_pass,
            passwords: self.passwords,
            state: Unlocked,
        }
    }
}

impl PasswordManager<Unlocked> {
    pub fn lock(self) -> PasswordManager<Locked> {
        PasswordManager {
            master_pass: self.master_pass,
            passwords: self.passwords,
            state: Locked,
        }
    }

    pub fn list_passwords(&self) -> &HashMap<String, String> {
        &self.passwords
    }

    pub fn add_password(&mut self, username: String, password: String) {
        self.passwords.insert(username, password);
    }
}

fn main() {
    let mut manager: PasswordManager = PasswordManager::new("password123".to_owned());
    let manager = manager.unlock("password123".to_owned());
    manager.list_passwords();
    let manager = manager.lock();
}
