#include "fake_factory.h"

#include <memory>

#include "envoy/registry/registry.h"
#include "envoy/server/transport_socket_config.h"

#include "source/common/config/datasource.h"
#include "source/common/config/utility.h"
#include "source/common/protobuf/message_validator_impl.h"
#include "source/common/protobuf/utility.h"

#include "contrib/envoy/extensions/private_key_providers/sgx/v3alpha/sgx.pb.h"
#include "contrib/envoy/extensions/private_key_providers/sgx/v3alpha/sgx.pb.validate.h"
#include "contrib/sgx/private_key_providers/source/sgx_private_key_provider.h"
#include "openssl/rsa.h"
#include "openssl/ssl.h"

namespace Envoy {
namespace Extensions {
namespace PrivateKeyMethodProvider {
namespace Sgx {

Ssl::PrivateKeyMethodProviderSharedPtr
FakeSgxPrivateKeyMethodFactory::createPrivateKeyMethodProviderInstance(
    const envoy::extensions::transport_sockets::tls::v3::PrivateKeyProvider& proto_config,
    Server::Configuration::TransportSocketFactoryContext& private_key_provider_context) {
  ProtobufTypes::MessagePtr message = std::make_unique<
      envoy::extensions::private_key_providers::sgx::v3alpha::SgxPrivateKeyMethodConfig>();

  Config::Utility::translateOpaqueConfig(proto_config.typed_config(),
                                         ProtobufMessage::getNullValidationVisitor(), *message);
  const envoy::extensions::private_key_providers::sgx::v3alpha::SgxPrivateKeyMethodConfig conf =
      MessageUtil::downcastAndValidate<
          const envoy::extensions::private_key_providers::sgx::v3alpha::SgxPrivateKeyMethodConfig&>(
          *message, private_key_provider_context.messageValidationVisitor());

  // std::shared_ptr<FakeLibSgxCryptoImpl>  = std::make_shared<FakeLibSgxCryptoImpl>();
  return std::make_shared<SgxPrivateKeyMethodProvider>(conf, private_key_provider_context);
}

} // namespace Sgx
} // namespace PrivateKeyMethodProvider
} // namespace Extensions
} // namespace Envoy
