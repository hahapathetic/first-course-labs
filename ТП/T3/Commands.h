#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include <vector>
#include "BaseStructs.h"
namespace mamonova {
  struct Commands
  {
    std::vector< Polygon > polygons_;
    void areaCommand();
    void maxCommand();
    void minCommand();
    void countCommand();
    void permsCommand();
    void rectsCommand();
    void invalidCommand(std::ostream& os);
    void emptyMessage(std::ostream& os);
  };
}
#endif
