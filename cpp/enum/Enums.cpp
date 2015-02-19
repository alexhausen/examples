#include <cassert>

#include <iostream>
#include <string>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/assign/list_of.hpp>

#define SEQ_Enums (Bounds) (FontSize)

#define DEFINE_ENUM_DECL_VAL(s, data, i, elem) \
        BOOST_PP_CAT(data, elem)

#define DEFINE_ENUM_DECL_VAL_COMMA(s, data, i, elem) \
        DEFINE_ENUM_DECL_VAL(s, data, i, elem),

#define __DEFINE_ENUM(name, prefix, seq, hook)   \
  typedef struct {                               \
    enum type {                                  \
      BOOST_PP_SEQ_FOR_EACH_I(hook, prefix, seq) \
    };                                           \
  } name

#define DEFINE_ENUM(name, prefix, seq)        \
        __DEFINE_ENUM(name, prefix, seq, DEFINE_ENUM_DECL_VAL_COMMA)

DEFINE_ENUM(Enum, k, SEQ_Enums);

#define DEFINE_ENUM_DECL_VAL(s, data, i, elem) \
        BOOST_PP_CAT(data, elem)

#define DEFINE_STR_TO_VAL(s, data, i, elem) \
  (BOOST_PP_STRINGIZE(DEFINE_ENUM_DECL_VAL(s, data, i, elem)) )

#define __DEFINE_ENUM_STRING(name, prefix, seq, hook) \
  static const std::vector<std::string> name =        \
      boost::assign::list_of<std::string>             \
      BOOST_PP_SEQ_FOR_EACH_I(hook, prefix, seq)

#define DEFINE_ENUM_TO_STRING(name, prefix, seq) \
        __DEFINE_ENUM_STRING(name, prefix, seq, DEFINE_STR_TO_VAL)

DEFINE_ENUM_TO_STRING(EnumString,, SEQ_Enums);

/*
 struct Enum {
 enum type { kBounds, kFontSize };
 };

 static const char* EnumString[] = { "bounds", "fontSize" };
 //*/

int main() {
	std::vector<std::string>::const_iterator it = EnumString.begin();
	for (; it != EnumString.end(); ++it) {
		if (!it->empty()) {
			std::string& s = const_cast<std::string&>(*it);
			s[0] = ::tolower(s[0]);
		}
	}
	Enum::type e1 = Enum::kBounds;
	std::cout << e1 << std::endl;
	std::string actual1 = EnumString[e1];
	std::cout << "actual1: " << actual1 << std::endl;
	assert(actual1 == "bounds");

	Enum::type e2 = Enum::kFontSize;
	std::cout << e2 << std::endl;
	std::string actual2 = EnumString[e2];
	std::cout << "actual2: " << actual2 << std::endl;
	assert(actual2 == "fontSize");

	return 0;
}

