#include "../../interface/interfaces.h"

template <typename T>
using MapT = std::unordered_map<std::string, std::shared_ptr<T>>;

using PairT = std::pair<std::shared_ptr<MapT<Operator> const>,
                        std::shared_ptr<MapT<UnaryOperator> const>>;
