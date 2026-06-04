# edge_chrome_policy_enable
DLL to spoof an MDM-managed device to enable all Edge &amp; Chrome policies

The only other method available online for spoofing OS MDM enrolment involves creating some fake MDM registry values, but unfortunately that also disables Defender tamper protection: https://hitco.at/blog/apply-edge-policies-for-non-domain-joined-devices/

This method involves placing mdmregistration.dll in the the same folder as msedge.exe or chrome.exe

The browser will then sideload our mdmregistration.dll, instead of the Windows one, and it always returns TRUE for IsDeviceRegisteredWithManagement
