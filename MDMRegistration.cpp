#include <windows.h>
#include <strsafe.h>

// Edge calls:
//   IsDeviceRegisteredWithManagement(&registered, 0, nullptr)
//   IsDeviceRegisteredWithManagement(&registered, 0x400, upnBuffer)
//
// Return a successful "registered" answer and optionally provide a UPN.
extern "C" __declspec(dllexport) HRESULT WINAPI IsDeviceRegisteredWithManagement(
    BOOL* pfIsDeviceRegisteredWithManagement,
    DWORD cchUPN,
    LPWSTR pszUPN) {
  if (pfIsDeviceRegisteredWithManagement == nullptr) {
    return E_INVALIDARG;
  }

  *pfIsDeviceRegisteredWithManagement = TRUE;

  if (pszUPN != nullptr && cchUPN != 0) {
    wchar_t configured_upn[512] = L"";
    DWORD chars = GetEnvironmentVariableW(
        L"EDGE_POLICY_MDM_UPN", configured_upn, ARRAYSIZE(configured_upn));

    const wchar_t* upn =
        (chars > 0 && chars < ARRAYSIZE(configured_upn))
            ? configured_upn
            : L"edge-policy-shim@example.invalid";

    HRESULT hr = StringCchCopyW(pszUPN, cchUPN, upn);
    if (FAILED(hr)) {
      return hr;
    }
  }

  return S_OK;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID) {
  return TRUE;
}
