#include "crypto.h"

#include <openssl/evp.h>
#include <string.h>

namespace utils {

namespace crypto {

void sha256_string(std::string string, std::string &outputBuffer) {
  EVP_MD_CTX *ctx = EVP_MD_CTX_new();
  /*EVP_MD_CTX ctx;
  unsigned int outLen;
  int i;

  const char *strP = string.c_str();
  char digest[EVP_MAX_MD_SIZE];

  EVP_DigestInit(&ctx, EVP_sha256());
  EVP_DigestUpdate(&ctx, strP, strlen(strP));
  EVP_DigestFinal(&ctx, digest, &outLen);*/

  /*unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  const char *strP = string.c_str();
  SHA256_Update(&sha256, strP, strlen(strP));
  SHA256_Final(hash, &sha256);
  int i = 0;
  char buff[65];
  for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    sprintf(buff + (i * 2), "%02x", hash[i]);
  }
  outputBuffer[64] = 0;
  outputBuffer = std::string(buff);*/
}

int sha256_file(std::string path, std::string &outputBuffer) {
  /*FILE *file = fopen(path, "rb");
  if (!file) return -534;

  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  const int bufSize = 32768;
  unsigned char *buffer = malloc(bufSize);
  int bytesRead = 0;
  if (!buffer) return ENOMEM;
  while ((bytesRead = fread(buffer, 1, bufSize, file))) {
    SHA256_Update(&sha256, buffer, bytesRead);
  }
  SHA256_Final(hash, &sha256);

  sha256_hash_string(hash, outputBuffer);
  fclose(file);
  free(buffer);*/
  return 0;
}

}  // namespace crypto

}  // namespace utils