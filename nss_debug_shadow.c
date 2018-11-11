#include <stdio.h>
#include <shadow.h>
#include <nss.h>

// Called to open the shadow file
enum nss_status _nss_debug_setspent(int stayopen)
{
  fprintf(stderr, "NSS DEBUG: Called %s with args (stayopen: %d)\n", __FUNCTION__, stayopen);
  return NSS_STATUS_SUCCESS;
}

// Called to close the shadow file
enum nss_status _nss_debug_endspent(void)
{
  fprintf(stderr, "NSS DEBUG: Called %s\n", __FUNCTION__);
  return NSS_STATUS_NOTFOUND;
}

// Called to look up next entry in the shadow file
enum nss_status _nss_debug_getspent_r(struct spwd *result, char *buffer, size_t buflen, int *errnop)
{
  fprintf(stderr, "NSS DEBUG: Called %s\n", __FUNCTION__);
  return NSS_STATUS_NOTFOUND;
}

// Find a shadow entry by name
enum nss_status _nss_debug_getspnam_r(const char *name, struct spwd *result, char *buffer, size_t buflen, int *errnop)
{
  fprintf(stderr, "NSS DEBUG: Called %s with args (name: %s)\n", __FUNCTION__, name);
  return NSS_STATUS_NOTFOUND;
}