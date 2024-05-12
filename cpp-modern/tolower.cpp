#include <locale>
#include <iostream>
#include <cassert>

//doesn't work

using namespace std;

int main() {
  auto loc = locale();
  auto& f = use_facet<ctype<wchar_t>>(loc);
  wchar_t wc = f.tolower(L'A');
  wstring ws;
  ws.push_back(wc);
  string s(ws.begin(), ws.end());
  cout << s << endl;

/*
  change_locale_to("en_US.utf8");
  assert(u8"abc" == to_lower(u8"AbC"));
  assert(u8"σ" == to_lower(u8"Σ"));
  assert(u8"ß" == to_lower(u8"ẞ"));
	assert("" == to_lower(""));

  change_locale_to("pt_BR.utf8");
  assert(u8"oáçã" == to_lower(u8"ÁÇÃO"));
*/
	return 0;
}

