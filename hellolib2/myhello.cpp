#include "coformat.h"
#include <string_view>

using namespace coformat;

int main() {
  cprintln("{fbr}{bd}Hello world");
  cprintln("{fby}{i}Hello world{ni}");
  cprintln("{fbm}{s}{bbk}Hello world{ns}");
  cprintln("{fbb}{b}Hello world{nb}");
  return 0;
}
