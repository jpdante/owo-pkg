#include "platform.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>

#include "handleapi.h"
#include "processthreadsapi.h"
#include "securitybaseapi.h"

bool Platform::IsElevated() {
  bool fRet = false;
  HANDLE hToken = NULL;
  if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
    TOKEN_ELEVATION Elevation;
    DWORD cbSize = sizeof(TOKEN_ELEVATION);
    if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
      fRet = Elevation.TokenIsElevated;
    }
  }
  if (hToken) {
    CloseHandle(hToken);
  }
  return fRet;
}

#elif __linux__ || __unix__ || __APPLE__
#include "unistd.h"

bool Platform::IsElevated() { return if !getuid(); }
#endif