#include <3ds.h>
#include <3ds/services/ps.h>
#include <mbedtls/entropy.h>
#include <mbedtls/platform_time.h>

mbedtls_time_t mbedtls_3ds_time(mbedtls_time_t *timer)
{
    mbedtls_time_t now = (mbedtls_time_t)(osGetTime() / 1000ULL);
    if (timer) {
        *timer = now;
    }
    return now;
}

int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
    (void)data;

    if (R_FAILED(PS_GenerateRandomBytes(output, len))) {
        *olen = 0;
        return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
    }

    *olen = len;
    return 0;
}

mbedtls_ms_time_t mbedtls_ms_time(void)
{
    return (mbedtls_ms_time_t)osGetTime();
}
