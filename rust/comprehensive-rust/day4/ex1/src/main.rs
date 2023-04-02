use std::sync::{Arc, Mutex};
use std::thread;
use std::time::Duration;

use rand::random;

struct Fork;

#[derive(Clone)]
struct Philosopher {
    name: String,
    left_fork: Arc<Mutex<Fork>>,
    right_fork: Arc<Mutex<Fork>>,
}

impl Philosopher {
    fn sleep(&self) {
        let r = (random::<u64>() % 10) + 1;
        thread::sleep(Duration::from_millis(r));
    }

    fn eat_and_think(&self) {
        // try to pick up forks...
        let left_result = self.right_fork.try_lock();
        let right_result = self.left_fork.try_lock();
        let result = left_result.and(right_result);
        match result {
            Ok(_) => {
                println!("{} is eating...", &self.name);
                let r = (random::<u64>() % 20) + 1;
                thread::sleep(Duration::from_millis(r));
                println!("Eureka! {} has a new idea!", &self.name);
            }
            Err(_) => {
                println!("{} could not eat this time...", &self.name);
            }
        }
    }
}

static PHILOSOPHERS: &[&str] = &["Socrates", "Plato", "Aristotle", "Thales", "Pythagoras"];

fn main() {
    let forks = (0..PHILOSOPHERS.len())
        .map(|_| Arc::new(Mutex::new(Fork)))
        .collect::<Vec<_>>();

    // Create philosophers
    let philosophers = PHILOSOPHERS
        .iter()
        .enumerate()
        .map(|(i, name)| Philosopher {
            name: name.to_string(),
            left_fork: forks[i].clone(),
            right_fork: forks[(i + 1) % PHILOSOPHERS.len()].clone(),
        })
        .collect::<Vec<Philosopher>>();

    // Make them think and eat
    let mut thread_handles: Vec<thread::JoinHandle<_>> = Vec::with_capacity(philosophers.len());
    philosophers.iter().for_each(|philosopher_ref| {
        let philosopher: Philosopher = philosopher_ref.clone();
        let thread_handle = thread::spawn(move || {
            for _ in 0..100 {
                philosopher.eat_and_think();
                philosopher.sleep();
            }
        });
        thread_handles.push(thread_handle);
    });

    // join threads
    for handle in thread_handles {
        handle.join().unwrap();
    }
    println!("done!");
}
