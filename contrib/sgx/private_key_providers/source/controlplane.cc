#include <unistd.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "envoy/registry/registry.h"
#include "envoy/server/transport_socket_config.h"

#include "source/common/common/base64.h"
#include "source/common/config/datasource.h"
#include "source/common/config/utility.h"

#include "contrib/sgx/private_key_providers/source/sgx_private_key_provider.h"

namespace Envoy {
namespace Extensions {
namespace PrivateKeyMethodProvider {
namespace Sgx {

void SgxPrivateKeyMethodProvider::initializeSgxEnclave() {
  CK_RV status = sgx_context_->sgxInit();
  if (status != CKR_OK) {
    throw EnvoyException("Failed to initialize sgx enclave.");
  }
}

void SgxPrivateKeyMethodProvider::findKeyPair() {

}

void SgxPrivateKeyMethodProvider::initialize(
    const envoy::extensions::private_key_providers::sgx::v3alpha::SgxPrivateKeyMethodConfig& config,
    Server::Configuration::TransportSocketFactoryContext& context) {

  initializeSgxEnclave();
  ENVOY_LOG(debug, "sgx private key provider: initializeSgxEnclave() finished");
}

} // namespace Sgx
} // namespace PrivateKeyMethodProvider
} // namespace Extensions
} // namespace Envoy
