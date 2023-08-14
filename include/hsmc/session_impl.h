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

#pragma once

#include "connector.h"

namespace hsmc {

class HSMC_API SessionImpl {
 public:
  using Ptr = std::shared_ptr<SessionImpl>;

  SessionImpl(Connector::Ptr connector);

  virtual ~SessionImpl();

  /// 打开会话
  virtual void open() = 0;

  /// 关闭会话
  virtual void close() = 0;

  /// 检查会话是否正常，recover为true时将自动执行connector的recover操作
  virtual bool isGood(int *errcode = nullptr, bool *recover = nullptr) const = 0;

  /// 获取会话句柄
  virtual void *getSessionHandle() const = 0;

  /// 获取会话id
  virtual std::string getId() const = 0;

  /// 获取连接器
  virtual Connector::Ptr getConnector();

  virtual int SDF_GetDeviceInfo(
      DEVICEINFO *pstDeviceInfo) const;

  virtual int SDF_GenerateRandom(
      unsigned int uiLength,
      unsigned char *pucRandom) const;

  virtual int SDF_GetPrivateKeyAccessRight(
      unsigned int uiKeyIndex,
      unsigned char *pucPassword,
      unsigned int uiPwdLength) const;

  virtual int SDF_ReleasePrivateKeyAccessRight(
      unsigned int uiKeyIndex) const;

  virtual int SDF_ExportSignPublicKey_RSA(
      unsigned int uiKeyIndex,
      RSArefPublicKey *pucPublicKey) const;

  virtual int SDF_ExportEncPublicKey_RSA(
      unsigned int uiKeyIndex,
      RSArefPublicKey *pucPublicKey) const;

  virtual int SDF_GenerateKeyPair_RSA(
      unsigned int uiKeyBits,
      RSArefPublicKey *pucPublicKey,
      RSArefPrivateKey *pucPrivateKey) const;

  virtual int SDF_GenerateKeyWithIPK_RSA(
      unsigned int uiIPKIndex,
      unsigned int uiKeyBits,
      unsigned char *pucKey,
      unsigned int *puiKeyLength,
      void **phKeyHandle) const;

  virtual int SDF_GenerateKeyWithEPK_RSA(
      unsigned int uiKeyBits,
      RSArefPublicKey *pucPublicKey,
      unsigned char *pucKey,
      unsigned int *puiKeyLength,
      void **phKeyHandle) const;

  virtual int SDF_ImportKeyWithISK_RSA(
      unsigned int uiISKIndex,
      unsigned char *pucKey,
      unsigned int uiKeyLength,
      void **phKeyHandle) const;

  virtual int SDF_ExchangeDigitEnvelopeBaseOnRSA(
      unsigned int uiKeyIndex,
      RSArefPublicKey *pucPublicKey,
      unsigned char *pucDEInput,
      unsigned int uiDELength,
      unsigned char *pucDEOutput,
      unsigned int *puiDELength) const;

  virtual int SDF_ExportSignPublicKey_ECC(
      unsigned int uiKeyIndex,
      ECCrefPublicKey *pucPublicKey) const;

  virtual int SDF_ExportEncPublicKey_ECC(
      unsigned int uiKeyIndex,
      ECCrefPublicKey *pucPublicKey) const;

  virtual int SDF_GenerateKeyPair_ECC(
      unsigned int uiAlgID,
      unsigned int uiKeyBits,
      ECCrefPublicKey *pucPublicKey,
      ECCrefPrivateKey *pucPrivateKey) const;

  virtual int SDF_GenerateKeyWithIPK_ECC(
      unsigned int uiIPKIndex,
      unsigned int uiKeyBits,
      ECCCipher *pucKey,
      void **phKeyHandle) const;

  virtual int SDF_GenerateKeyWithEPK_ECC(
      unsigned int uiKeyBits,
      unsigned int uiAlgID,
      ECCrefPublicKey *pucPublicKey,
      ECCCipher *pucKey,
      void **phKeyHandle) const;

  virtual int SDF_ImportKeyWithISK_ECC(
      unsigned int uiISKIndex,
      ECCCipher *pucKey,
      void **phKeyHandle) const;

  virtual int SDF_GenerateAgreementDataWithECC(
      unsigned int uiISKIndex,
      unsigned int uiKeyBits,
      unsigned char *pucSponsorID,
      unsigned int uiSponsorIDLength,
      ECCrefPublicKey *pucSponsorPublicKey,
      ECCrefPublicKey *pucSponsorTmpPublicKey,
      void **phAgreementHandle) const;

  virtual int SDF_GenerateKeyWithECC(
      unsigned char *pucResponseID,
      unsigned int uiResponseIDLength,
      ECCrefPublicKey *pucResponsePublicKey,
      ECCrefPublicKey *pucResponseTmpPublicKey,
      void *hAgreementHandle,
      void **phKeyHandle) const;

  virtual int SDF_GenerateAgreementDataAndKeyWithECC(
      unsigned int uiISKIndex,
      unsigned int uiKeyBits,
      unsigned char *pucResponseID,
      unsigned int uiResponseIDLength,
      unsigned char *pucSponsorID,
      unsigned int uiSponsorIDLength,
      ECCrefPublicKey *pucSponsorPublicKey,
      ECCrefPublicKey *pucSponsorTmpPublicKey,
      ECCrefPublicKey *pucResponsePublicKey,
      ECCrefPublicKey *pucResponseTmpPublicKey,
      void **phKeyHandle) const;

  virtual int SDF_ExchangeDigitEnvelopeBaseOnECC(
      unsigned int uiKeyIndex,
      unsigned int uiAlgID,
      ECCrefPublicKey *pucPublicKey,
      ECCCipher *pucEncDataIn,
      ECCCipher *pucEncDataOut) const;

  virtual int SDF_GenerateKeyWithKEK(
      unsigned int uiKeyBits,
      unsigned int uiAlgID,
      unsigned int uiKEKIndex,
      unsigned char *pucKey,
      unsigned int *puiKeyLength,
      void **phKeyHandle) const;

  virtual int SDF_ImportKeyWithKEK(
      unsigned int uiAlgID,
      unsigned int uiKEKIndex,
      unsigned char *pucKey,
      unsigned int uiKeyLength,
      void **phKeyHandle) const;

  virtual int SDF_ImportKey(
      unsigned char *pucKey,
      unsigned int uiKeyLength,
      void **phKeyHandle) const;

  virtual int SDF_DestroyKey(
      void *hKeyHandle) const;

  virtual int SDF_ExternalPublicKeyOperation_RSA(
      RSArefPublicKey *pucPublicKey,
      unsigned char *pucDataInput,
      unsigned int uiInputLength,
      unsigned char *pucDataOutput,
      unsigned int *puiOutputLength) const;

  virtual int SDF_InternalPublicKeyOperation_RSA(
      unsigned int uiKeyIndex,
      unsigned char *pucDataInput,
      unsigned int uiInputLength,
      unsigned char *pucDataOutput,
      unsigned int *puiOutputLength) const;

  virtual int SDF_InternalPrivateKeyOperation_RSA(
      unsigned int uiKeyIndex,
      unsigned char *pucDataInput,
      unsigned int uiInputLength,
      unsigned char *pucDataOutput,
      unsigned int *puiOutputLength) const;

  virtual int SDF_ExternalPrivateKeyOperation_RSA(
      RSArefPrivateKey *pucPrivateKey,
      unsigned char *pucDataInput,
      unsigned int uiInputLength,
      unsigned char *pucDataOutput,
      unsigned int *puiOutputLength) const;

  virtual int SDF_ExternalSign_ECC(
      unsigned int uiAlgID,
      ECCrefPrivateKey *pucPrivateKey,
      unsigned char *pucData,
      unsigned int uiDataLength,
      ECCSignature *pucSignature) const;

  virtual int SDF_ExternalVerify_ECC(
      unsigned int uiAlgID,
      ECCrefPublicKey *pucPublicKey,
      unsigned char *pucDataInput,
      unsigned int uiInputLength,
      ECCSignature *pucSignature) const;

  virtual int SDF_InternalSign_ECC(
      unsigned int uiISKIndex,
      unsigned char *pucData,
      unsigned int uiDataLength,
      ECCSignature *pucSignature) const;

  virtual int SDF_InternalVerify_ECC(
      unsigned int uiIPKIndex,
      unsigned char *pucData,
      unsigned int uiDataLength,
      ECCSignature *pucSignature) const;

  virtual int SDF_ExternalEncrypt_ECC(
      unsigned int uiAlgID,
      ECCrefPublicKey *pucPublicKey,
      unsigned char *pucData,
      unsigned int uiDataLength,
      ECCCipher *pucEncData) const;

  virtual int SDF_ExternalDecrypt_ECC(
      unsigned int uiAlgID,
      ECCrefPrivateKey *pucPrivateKey,
      ECCCipher *pucEncData,
      unsigned char *pucData,
      unsigned int *puiDataLength) const;

  virtual int SDF_Encrypt(
      void *hKeyHandle,
      unsigned int uiAlgID,
      unsigned char *pucIV,
      unsigned char *pucData,
      unsigned int uiDataLength,
      unsigned char *pucEncData,
      unsigned int *puiEncDataLength) const;

  virtual int SDF_Decrypt(
      void *hKeyHandle,
      unsigned int uiAlgID,
      unsigned char *pucIV,
      unsigned char *pucEncData,
      unsigned int uiEncDataLength,
      unsigned char *pucData,
      unsigned int *puiDataLength) const;

  virtual int SDF_CalculateMAC(
      void *hKeyHandle,
      unsigned int uiAlgID,
      unsigned char *pucIV,
      unsigned char *pucData,
      unsigned int uiDataLength,
      unsigned char *pucMAC,
      unsigned int *puiMACLength) const;

  virtual int SDF_HashInit(
      unsigned int uiAlgID,
      ECCrefPublicKey *pucPublicKey,
      unsigned char *pucID,
      unsigned int uiIDLength) const;

  virtual int SDF_HashUpdate(
      unsigned char *pucData,
      unsigned int uiDataLength) const;

  virtual int SDF_HashFinal(
      unsigned char *pucHash,
      unsigned int *puiHashLength) const;

  virtual int SDF_CreateFile(
      unsigned char *pucFileName,
      unsigned int uiNameLen,/* max 128-byte */
      unsigned int uiFileSize) const;

  virtual int SDF_ReadFile(
      unsigned char *pucFileName,
      unsigned int uiNameLen,
      unsigned int uiOffset,
      unsigned int *puiFileLength,
      unsigned char *pucBuffer) const;

  virtual int SDF_WriteFile(
      unsigned char *pucFileName,
      unsigned int uiNameLen,
      unsigned int uiOffset,
      unsigned int uiFileLength,
      unsigned char *pucBuffer) const;

  virtual int SDF_DeleteFile(
      unsigned char *pucFileName,
      unsigned int uiNameLen) const;

  virtual int SVS_ExportCert(
      const char *certId,
      uint8_t *certData,
      uint32_t *certDataLen) const;

  virtual int SVS_ParseCert(
      int certType,
      const uint8_t *certData,
      uint32_t certDataLen,
      uint8_t *certInfo,
      uint32_t *certInfoLen) const;

  virtual int SVS_ValidateCert(
      const uint8_t *certData,
      uint32_t certDataLen,
      bool ocsp,
      int *state) const;

  virtual int SVS_SignData(
      int method,
      uint32_t signPrivateKeyIndex,
      const char *password,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *signData,
      uint32_t *signDataLen) const;

  virtual int SVS_VerifySignedData(
      int type,
      const uint8_t *certData,
      uint32_t certDataLen,
      const uint8_t *data,
      uint32_t dataLen,
      const uint8_t *signData,
      uint32_t signDataLen,
      int verifyLevel) const;

  virtual int SVS_SignDataInit(
      int method,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *hashData,
      uint32_t *hashDataLen) const;

  virtual int SVS_SignDataUpdate(
      int method,
      const uint8_t *hashMediantData,
      uint32_t hashMediantDataLen,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *hashData,
      uint32_t *hashDataLen) const;

  virtual int SVS_SignDataFinal(
      int method,
      uint32_t signPrivateKeyIndex,
      const char *password,
      const uint8_t *hashMediantData,
      uint32_t hashMediantDataLen,
      uint8_t *signData,
      uint32_t *signDataLen) const;

  virtual int SVS_VerifySignedDataInit(
      int method,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *hashData,
      uint32_t *hashDataLen) const;

  virtual int SVS_VerifySignedDataUpdate(
      int method,
      const uint8_t *hashMediantData,
      uint32_t hashMediantDataLen,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *hashData,
      uint32_t *hashDataLen) const;

  virtual int SVS_VerifySignedDataFinal(
      int method,
      int type,
      const uint8_t *certData,
      uint32_t certDataLen,
      const uint8_t *hashMediantData,
      uint32_t hashMediantDataLen,
      const uint8_t *signData,
      uint32_t signDataLen,
      int verifyLevel) const;

  virtual int SVS_SignMessage(
      int method,
      uint32_t signPrivateKeyIndex,
      const char *password,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *signData,
      uint32_t *signDataLen,
      bool isHashFlag,
      bool isOriginalText,
      bool isCertificateChain,
      bool isCrl,
      bool isAuthenticationAttributes) const;

  virtual int SVS_VerifySignedMessage(
      const uint8_t *data,
      uint32_t dataLen,
      const uint8_t *signData,
      uint32_t signDataLen,
      bool isHashFlag,
      bool isOriginalText,
      bool isCertificateChain,
      bool isCrl,
      bool sAuthenticationAttributes) const;

  virtual int SVS_SignMessageInit(
      int method,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *hashData,
      uint32_t *hashDataLen) const;

  virtual int SVS_SignMessageUpdate(
      int method,
      const uint8_t *hashMediantData,
      uint32_t hashMediantDataLen,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *hashData,
      uint32_t *hashDataLen) const;

  virtual int SVS_SignMessageFinal(
      int method,
      uint32_t signPrivateKeyIndex,
      const char *password,
      const uint8_t *hashMediantData,
      uint32_t hashMediantDataLen,
      uint8_t *signData,
      uint32_t *signDataLen) const;

  virtual int SVS_VerifySignedMessageInit(
      int method,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *hashData,
      uint32_t *hashDataLen) const;

  virtual int SVS_VerifySignedMessageUpdate(
      int method,
      const uint8_t *hashMediantData,
      uint32_t hashMediantDataLen,
      const uint8_t *data,
      uint32_t dataLen,
      uint8_t *hashData,
      uint32_t *hashDataLen) const;

  virtual int SVS_VerifySignedMessageFinal(
      int method,
      const uint8_t *hashMediantData,
      uint32_t hashMediantDataLen,
      const uint8_t *signData,
      uint32_t signDataLen) const;

  virtual SGD_UINT32 STF_CreateTSRequest(
      SGD_UINT8 *pucInData,
      SGD_UINT32 uiInDataLength,
      SGD_UINT32 uiReqType,
      SGD_UINT8 *pucTSExt,
      SGD_UINT32 uiTSExtLength,
      SGD_UINT32 uiHashAlgID,
      SGD_UINT8 *pucTSRequest,
      SGD_UINT32 *puiTSRequestLength) const;

  virtual SGD_UINT32 STF_CreateTSResponse(
      SGD_UINT8 *pucTSRequest,
      SGD_UINT32 uiTSRequestLength,
      SGD_UINT32 uiSignatureAlgID,
      SGD_UINT8 *pucTSResponse,
      SGD_UINT32 *puiTSResponseLength) const;

  virtual SGD_UINT32 STF_VerifyTSValidity(
      SGD_UINT8 *pucTSResponse,
      SGD_UINT32 uiTSResponseLength,
      SGD_UINT32 uiHashAlgID,
      SGD_UINT32 uiSignatureAlgID,
      SGD_UINT8 *pucTSCert,
      SGD_UINT32 uiTSCertLength) const;

  virtual SGD_UINT32 STF_GetTSInfo(
      SGD_UINT8 *pucTSResponse,
      SGD_UINT32 uiTSResponseLength,
      SGD_UINT8 *pucIssuerName,
      SGD_UINT32 *puiIssuerNameLength,
      SGD_UINT8 *pucTime,
      SGD_UINT32 *puiTimeLength) const;

  virtual SGD_UINT32 STF_GetTSDetail(
      SGD_UINT8 *pucTSResponse,
      SGD_UINT32 uiTSResponseLength,
      SGD_UINT32 uiItemNumber,
      SGD_UINT8 *pucItemValue,
      SGD_UINT32 *puiItemValueLength) const;

 protected:
  Connector::Ptr connector_;

 private:
  SessionImpl();
  SessionImpl(const SessionImpl &);
  SessionImpl &operator=(const SessionImpl &);
};

}
