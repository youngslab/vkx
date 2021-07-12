#pragma once

#include <vector>
#include <algorithm>

namespace vkx {

template <typename T> auto ToNativeVector(std::vector<T> const &objects) {
  return std::transform(objects.begin(), objects.end(),
			[](auto const &obj) { return obj.GetValue(); });
}

template <typename T> auto ToNativeVector(T const &object) {
	return std::vector{ object.GetValue() };
}

} // namespace vkx
