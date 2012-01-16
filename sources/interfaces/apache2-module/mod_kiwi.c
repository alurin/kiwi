/**
 *
 */

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include <unicode/uclean.h>

static void kiwi_register_hooks(apr_pool_t *p)
{
    /// init ICU for MT
    UErrorCode errorCode;
    u_init(&errorCode); /// Move to the right place

    // ap_hook_handler(kiwi_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA kiwi_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    kiwi_register_hooks    /* register hooks                      */
};

