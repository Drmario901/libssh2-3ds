# libssh2-3ds

Minimal Nintendo 3DS `libssh2` port bundle.

This repository keeps only the reusable SSH dependency artifacts from the old
3DS SSH client prototype:

- `third_party/3ds/include/libssh2*.h`
- `third_party/3ds/lib/libssh2.a`
- required mbedTLS/PSA headers and static libraries
- `third_party/mbedtls_3ds_config.h`
- `source/platform/mbedtls_3ds.c`

The old application, renderer, terminal, build output, crash dumps, and local
prototype code are intentionally ignored.

## Link Notes

For a devkitPro 3DS project, link the SSH bundle before the 3DS system libs:

```make
LIBS += -lssh2 -lmbedtls -lmbedx509 -lmbedcrypto -lcitro2d -lcitro3d -lctru -lm
LIBDIRS += $(CURDIR)/third_party/3ds
INCLUDES += include third_party/3ds/include
```

The mbedTLS 3DS shim provides time and entropy hooks through libctru:

- `osGetTime()`
- `PS_GenerateRandomBytes()`

Initialize `psInit()` before using the entropy hook, and call
`mbedtls_platform_set_time(mbedtls_3ds_time)` during platform startup.
