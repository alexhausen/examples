#include <iostream>
#include <boost/preprocessor.hpp>

struct Fruit1 {
	enum type { Banana, Orange, Apple };
};


#define SEQ_FRUITS2 (Pineapple)(Raspberry)(Avocado)

struct Fruit2 {
	enum type {
		BOOST_PP_SEQ_ENUM(SEQ_FRUITS2)
	};
};


//#define SEQ_FIRST (r, data, elem) BOOST_PP_TUPLE_ELEM(2, 0, elem)
//BOOST_PP_CAT(elem, cat)
//BOOST_PP_TUPLE_ELEM(2, 0, elem)

//#define MACRO (r, data, elem) BOOST_PP_CAT(elem, BOOST_PP_COMMA)
//#define SEQ_FRUITS3 (Cherry, "Cereja")(Coconut, "Coco")(Cashew, "Caju")
//#define SEQ_FRUITS3_VAL BOOST_PP_FOR_EACH(MACRO, , SEQ_FRUITS3)


struct Fruit3 {
	enum type {
		BOOST_PP_SEQ_ENUM(SEQ_FRUITS2)
	};
};

int main() {
	Fruit1::type f1 = Fruit1::Orange;
	std::cout << f1 << std::endl;

	Fruit2::type f2 = Fruit2::Avocado;
	std::cout << f2 << std::endl;
	
	return 0;


}
