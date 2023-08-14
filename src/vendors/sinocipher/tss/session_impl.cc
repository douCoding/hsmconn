// Copyright (C) 2021 Institute of Data Security, HIT
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "session_impl.h"
#include "connector.h"

#include <utility>
#include "utils/uuid.h"
#include <absl/strings/str_format.h>

namespace hsmc {
namespace tss {
namespace sinocipher {

SessionImpl::SessionImpl(hsmc::Connector::Ptr connector)
    : hsmc::SessionImpl(std::move(connector)), hSession_(nullptr) {
}

SessionImpl::~SessionImpl() = default;

void SessionImpl::open() {
  if (hSession_ == nullptr) {
    auto connect = dynamic_cast<hsmc::tss::sinocipher::Connector *>(connector_.get());
    if (nullptr == connect) {
      throw SdfExcuteException(absl::StrFormat(
          "Fail to dynamic_cast from hsmc::Connector to hsmc::tss::sinocipher::Connector"));
    }
    int rc = connect->STF_InitEnvironment_Ex_(&hSession_, (SGD_UINT8 *)connect->getConfig().c_str());
    if (0 != rc) {
      throw SdfExcuteException(absl::StrFormat("Fail to open %s device session",
                                               connector_->getName().c_str()), rc);
    }

    id_ = connector_->getName() + "-" + hsmc::util::generate_uuid(16);
  }
}

void SessionImpl::close() {
  if (hSession_ != nullptr) {
    int rc = connector_->STF_ClearEnvironment(hSession_);
    if (0 != rc) {
      throw SdfExcuteException(absl::StrFormat("Fail to close %s device session",
                                               connector_->getName().c_str()), rc);
    }
    hSession_ = nullptr;
  }
}

bool SessionImpl::isGood(int *errcode, bool *dev_reopen) const {
  if (nullptr == hSession_) {
    return false;
  }

  uint8_t plain[6] = {0};
  uint8_t ts_request[1024] = {0};
  uint32_t ts_request_len = sizeof(ts_request);
  return 0 == connector_->STF_CreateTSRequest(hSession_, plain, sizeof(plain), 1,
                                              nullptr, 0, SGD_SM3, ts_request, &ts_request_len);
}

void *SessionImpl::getSessionHandle() const {
  return hSession_;
}

std::string SessionImpl::getId() const {
  return id_;
}

}
}
}