/*
Animal Shelter: An animal shelter, which holds only dogs and cats, operates on
a strictly "first in, first out" basis. People must adopt either the "oldest"
(based on arrival time) of all animals at the shelter, or they can select
whether they would prefer a dog or a cat (and will receive the oldest animal of
that type). They cannot select which specific animal they would like. Create
the data structures to maintain this system and implement operations such as
enqueue, dequeueAny, dequeueDog, and dequeueCat.
You may use the built-in Linked list data structure.
Hints: #22, #56, #63
*/

#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <memory>
#include <algorithm>

enum class animal_t { cat, dog };

class Animal {
 public:
  animal_t type_;
  std::string name_;

  Animal(animal_t type, const std::string& name) : type_{type}, name_{name} {}
};

class AnimalShelter {
 public:
  void enqueue(std::unique_ptr<Animal> animal) {
    animals_.push_back(std::move(animal));
  }

  std::unique_ptr<Animal> dequeueAny() {
    std::unique_ptr<Animal> any = std::move(animals_.front());
    animals_.pop_front();
    return any;
  }
  
  std::unique_ptr<Animal> dequeueDog() {
    return dequeueAnimal(animal_t::dog);
  }
  
  std::unique_ptr<Animal> dequeueCat() {
    return dequeueAnimal(animal_t::cat);
  }

  bool empty() const {
    return animals_.empty();
  }

 private:
  std::unique_ptr<Animal> dequeueAnimal(animal_t type) {
    auto it = std::find_if(animals_.begin(), animals_.end(), [=](const auto& p){return p->type_ == type;});
    if (it == animals_.end()) {
      return {};
    }
    std::unique_ptr<Animal> animal = std::move(*it);
    animals_.erase(it);
    return animal;
  }

  std::list<std::unique_ptr<Animal>> animals_;
};

int main() {
  AnimalShelter shelter;
  auto felix = std::make_unique<Animal>(animal_t::cat, "Felix");
  auto rex = std::make_unique<Animal>(animal_t::dog, "Rex");
  auto toto = std::make_unique<Animal>(animal_t::dog, "Toto");
  auto kitkat = std::make_unique<Animal>(animal_t::cat, "KitKat");
  shelter.enqueue(std::move(felix));
  shelter.enqueue(std::move(rex));
  shelter.enqueue(std::move(toto));
  shelter.enqueue(std::move(kitkat));
  auto r1 = shelter.dequeueDog();
  assert("Rex" == r1->name_);
  auto r2 = shelter.dequeueAny();
  assert("Felix" == r2->name_);
  auto r3 = shelter.dequeueCat();
  assert("KitKat" == r3->name_);
  auto r4 = shelter.dequeueAny();
  assert("Toto" == r4->name_);
  assert(shelter.empty());
  std::cout << "OK" << std::endl; }
