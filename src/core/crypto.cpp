#include "crypto.hpp"

#include <openssl/evp.h>
#include <string.h>

#include <fstream>

namespace owo::core {

void Sha256String(std::string string, std::string &output) {
  const char *strP = string.c_str();
  unsigned char digest[EVP_MAX_MD_SIZE];
  unsigned int outLen;

  EVP_MD_CTX *ctx = EVP_MD_CTX_new();
  EVP_DigestInit(ctx, EVP_sha256());
  EVP_DigestUpdate(ctx, strP, strlen(strP));
  EVP_DigestFinal(ctx, digest, &outLen);
  EVP_MD_CTX_destroy(ctx);

  char hash[EVP_MAX_MD_SIZE];
  for (int i = 0; i < outLen; i++) {
    sprintf(hash + (i * 2), "%02x", digest[i]);
  }
  output = std::string(hash);
}

bool Sha256File(std::filesystem::path path, std::string &output) {
  unsigned char digest[EVP_MAX_MD_SIZE];
  unsigned int outLen;

  std::fstream file;
  file.open(path, std::ios::in | std::ios::binary);
  if (!file.is_open()) return false;

  EVP_MD_CTX *ctx = EVP_MD_CTX_new();
  EVP_DigestInit(ctx, EVP_sha256());
  const int bufSize = 32768;
  while (!file.eof() && file.is_open()) {
    char buffer[bufSize];
    file.read(buffer, bufSize);
    EVP_DigestUpdate(ctx, buffer, file.gcount());
  }
  EVP_DigestFinal(ctx, digest, &outLen);
  EVP_MD_CTX_destroy(ctx);

  file.close();

  char hash[EVP_MAX_MD_SIZE];
  for (int i = 0; i < outLen; i++) {
    sprintf(hash + (i * 2), "%02x", digest[i]);
  }
  output = std::string(hash);
  return true;
}

}  // namespace owo::core