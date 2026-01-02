#include "coformat.h"
#include <string>
#include <string_view>

using namespace coformat;

std::string greetings(std::string_view m_name) {
  return cformat("{fby}{b}{u}Hello {}{nu}{nb}", m_name);
}

int main() {
  cprintln("{fr}Hello world");

  std::string hello_john = greetings("John Pombe");
  cprintln("{}", hello_john);

  return 0;
}
