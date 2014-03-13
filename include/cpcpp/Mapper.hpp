
#pragma once

namespace cpcpp {

// In theory, a simpler way to call std::transform.
// todo: Make this return-type agnostic. Probably
// specialize something to optionally call "reserve"
// and create inserters.
template <typename C, typename F>
auto Map (const C& container, F func)
  -> std::vector<decltype (func (* container . begin ()))>
{ decltype (Map (container, func)) output;
  output . reserve (container . size ());
  std::transform (container . begin (),
                  container . end (),
                  std::back_inserter (output),
                  func);
  return output;
}


}
