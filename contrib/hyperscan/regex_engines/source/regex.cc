#include "contrib/hyperscan/regex_engines/source/regex.h"

namespace Envoy {
namespace Extensions {
namespace Regex {
namespace Hyperscan {

HyperscanEngine::HyperscanEngine(ThreadLocal::SlotAllocator& tls) : tls_(tls) {}

Envoy::Regex::CompiledMatcherPtr HyperscanEngine::matcher(const std::string& regex) const {
  std::vector<const char*> expressions{regex.c_str()};
  std::vector<unsigned int> flags{HS_FLAG_UTF8};
  std::vector<unsigned int> ids{0};

  IS_ENVOY_BUG(fmt::format("DEBUG!!! Hyperscan"));
  return std::make_unique<Matching::InputMatchers::Hyperscan::Matcher>(expressions, flags, ids,
                                                                       tls_, true);
}

} // namespace Hyperscan
} // namespace Regex
} // namespace Extensions
} // namespace Envoy
