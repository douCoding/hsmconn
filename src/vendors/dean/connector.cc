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

#include "connector.h"

#include <absl/strings/str_format.h>
#include <stdlib.h>

#include <memory>

#include "hsmc/connector.h"
#include "hsmc/exception.h"
#include "session_impl.h"

namespace hsmc {
namespace dean {

Connector::Connector(const std::string &nativeLibPath) : hsmc::Connector(nativeLibPath), hDevice_(nullptr) {
}

Connector::Connector() : hDevice_(nullptr) {
}

Connector::~Connector() = default;

hsmc::SessionImpl::Ptr Connector::createSession() {
  open();
  hsmc::SessionImpl::Ptr p(new SessionImpl(shared_from_this()));
  p->open();

  return p;
}

void Connector::open() {
  std::lock_guard<std::mutex> guard(this->mutex_);
  if (isOpen()) return;

  // 打开连接器
  hsmc::Connector::open();

  // 打开设备
  int rc = 0;

  if (SDR_OK != (rc = SDF_OpenDevice(&hDevice_))) {
    std::string errorMsg = absl::StrFormat("[%s] fail to execute SDF_OpenDevice", getName().c_str());

    throw SdfExcuteException(errorMsg, rc);
  }

  // SDF_OpenDeviceWithPath_ = FUNC_INITIALIZER(SDF_OpenDeviceWithPath);
  // rc = SDF_OpenDeviceWithPath_((char *)getConfig().c_str(), &hDevice_);
  // if (SDR_OK != rc) {
  //   std::string errorMsg = absl::StrFormat("[%s] fail to execute SDF_OpenDeviceWithPath", getName().c_str());
  //   throw SdfExcuteException(errorMsg, rc);
  // }

  SDF_GetSesKey_ = FUNC_INITIALIZER(SDF_GetSesKey);
}

void Connector::close() {
  if (hDevice_ != nullptr) {
    // 关闭设备
    int rc = SDF_CloseDevice(hDevice_);
    if (SDR_OK != rc) {
      std::string errorMsg = absl::StrFormat("[%s] fail to execute SDF_OpenDevice", getName().c_str());
      throw SdfExcuteException(errorMsg, rc);
    }

    hDevice_ = nullptr;
  }

  // 关闭连接器
  hsmc::Connector::close();
}

void Connector::reopen() {
}

int Connector::SDF_GetSesKey(void *hSessionHandle, void *phKeyHandle) {
  return SDF_GetSesKey_(hSessionHandle, phKeyHandle);
}

}  // namespace dean
}  // namespace hsmc