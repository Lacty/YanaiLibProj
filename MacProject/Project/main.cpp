
#include "lib/app.hpp"


int main() {
  App app(500, 500, "Test");
  app.setClearColor(Color::gray());
  
  while(app.isOpen()) {
    app.letsStart();
    
  }
}
