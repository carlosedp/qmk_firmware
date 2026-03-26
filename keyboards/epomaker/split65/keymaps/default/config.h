/*
 * Use a RGB_MATRIX_TIMEOUT that is less than the sleep timeouts to
 * make sure the RGB will be turned off.
 */
#define RGB_MATRIX_TIMEOUT 120000 // 2 minutes
/*
 * There are two different sleep timeouts, one in wls.h and one is in lowpower.c.
 *
 * Override the default HS_SLEEP_TIMEOUT of 5 minutes by defining it here.
 * Ex. HS_SLEEP_TIMEOUT 120000 for 2 minutes
 *
 * Override the default LPWR_TIMEOUT of 5 minutes by defining it here.
 * Ex. LPWR_TIMEOUT 600000 for 10 minutes
 */
#define HS_SLEEP_TIMEOUT 300000 // 5 minutes
#define LPWR_TIMEOUT 600000 // 10 minutes
