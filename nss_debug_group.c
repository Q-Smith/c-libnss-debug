#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>
#include <malloc.h>
#include <grp.h>
#include <nss.h>

enum nss_status _nss_debug_initgroups_dyn(const char *user, gid_t gid, long int *start, long int *size, gid_t **groupsp, long int limit, int *errnop) {
  fprintf(stderr, "NSS DEBUG: Called %s with args (user: %s)(gid: %d)\n", __FUNCTION__, user, gid);

  if (strcmp(user, "super_user") == 0) {
    if (*start == *size) {
      if (limit > 0) {
        if (*size < limit) {
          *size = (limit < (*size * 2)) ? limit : (*size * 2);
        } else {
          syslog(LOG_ERR, "initgroups_dyn: limit was too low\n");
          *errnop = ERANGE;
          return NSS_STATUS_TRYAGAIN;
        }
      } else {
        (*size) = (*size) * 2;
      }
      *groupsp = realloc(*groupsp, sizeof(**groupsp) * (*size));
    }
    (*groupsp)[*start] = 110; // the new super group
    (*start)++;

    *groupsp = realloc(*groupsp, sizeof(**groupsp) * (*start));
    *size = *start;
  }

  return NSS_STATUS_SUCCESS;
}

// Called to open the group file
enum nss_status _nss_debug_setgrent(int stayopen)
{
  fprintf(stderr, "NSS DEBUG: Called %s with args (stayopen: %d)\n", __FUNCTION__, stayopen);
  return NSS_STATUS_SUCCESS;
}

// Called to close the group file
enum nss_status _nss_debug_endgrent(void)
{
  fprintf(stderr, "NSS DEBUG: Called %s\n", __FUNCTION__);
  return NSS_STATUS_NOTFOUND;
}

// Called to look up next entry in group file
enum nss_status _nss_debug_getgrent_r(struct group *result, char *buffer, size_t buflen, int *errnop)
{
  fprintf(stderr, "NSS DEBUG: Called %s\n", __FUNCTION__);
  return NSS_STATUS_NOTFOUND;
}

// Find a group by gid
enum nss_status _nss_debug_getgrgid_r(gid_t gid, struct group *result, char *buffer, size_t buflen, int *errnop)
{
  fprintf(stderr, "NSS DEBUG: Called %s with args (gid: %d)\n", __FUNCTION__, gid);
  return NSS_STATUS_NOTFOUND;
}

// Find a group by name
enum nss_status _nss_debug_getgrnam_r(const char *name, struct group *result, char *buffer, size_t buflen, int *errnop)
{
  fprintf(stderr, "NSS DEBUG: Called %s with args (name: %s)\n", __FUNCTION__, name);
  return NSS_STATUS_NOTFOUND;
}