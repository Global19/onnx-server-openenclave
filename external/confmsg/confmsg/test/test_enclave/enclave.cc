// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <stdexcept>
#include <iostream>
#include <openenclave/enclave.h>

#include "server/api.h"
#include "test_t.h"  // generated by oeedger8r

static confmsg::Server* server = nullptr;

static int ServerFunction(std::vector<uint8_t>& data) {
  // TODO do something with data?
  (void)data;
  return 0;
}

extern "C" void EnclaveInitialize() {
  try {
    std::vector<uint8_t> service_identifier;
    auto key_provider = confmsg::RandomEd25519KeyProvider::Create();
    server = new confmsg::Server(service_identifier, ServerFunction, std::move(key_provider));
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    abort();
  }
}

extern "C" void EnclaveRespondToMessage(const uint8_t* msg, size_t msg_size, uint8_t* out_msg, size_t* out_msg_size, size_t max_out_msg_size) {
  try {
    server->RespondToMessage(msg, msg_size, out_msg, out_msg_size, max_out_msg_size);
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    abort();
  }
}

extern "C" void EnclaveDestroy() {
  delete server;
  server = nullptr;
}