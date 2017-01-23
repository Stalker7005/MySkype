#pragma once

#include <cstdio>
#include <cstdlib>
#include <functional>
#include <type_traits>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <boost/unordered_set.hpp>
#include <map>
#include <unordered_map>
#include <boost/unordered_map.hpp>
#include <boost/cstdint.hpp>
#include <boost/smart_ptr.hpp>
#include <cstdint>
#include <memory>
#include "Blob.h"

template<class T>
struct is_trivially_serializable : std::integral_constant < bool, 
    std::is_object<T>::value && std::is_standard_layout<T>::value && std::alignment_of<T>::value == 1> {};

