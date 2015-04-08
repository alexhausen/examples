#include <iostream>
#include <regex>
#include <string>
 
using namespace std;
 
int main() {
  string s = "Content-Type: multipart/mixed;boundary=\"bbb\"";
  const regex r{R"(Content-Type: multipart/mixed;boundary=\"(\w+)\")"};
  smatch sm;
  if (regex_match(s, sm, r)) {
    cout << "yes " << sm[1] << endl;
  } else {
    cout << "no" << endl;
  }
 
  return 0;
}
