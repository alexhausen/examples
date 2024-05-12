#include "enum.h"

enum class fruit_enum { banana, apple, pinaple };

//FruitEnum can be foward declared
class FruitEnum : public Enum<fruit_enum> {
public:
  FruitEnum(fruit_enum f);
  void set(const std::string& s) override;
  std::string str() const override;
};
