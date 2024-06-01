# Development Dependencies

NvRest use h2o proven http1.1/http2 webserver as the underlying http server.

## Shared Dependencies
- Lib H2O Http Server >= v2.5
- OpenSSL >= v1.1
- Lib UV
- Lib Wslay
- Zlib

Note: Debian or Ubuntu linux based
```shell
sudo apt-get update && \
sudo apt-get install \
    libh2o-dev \
    openssl \
    libssl-dev \
    libuv1-dev \
    libwslay-dev \
    zlib1g-dev
```

## Checking your shared-lib
In linux you can check for already installed shared library by executing this command
```shell
dpkg-query -l | grep libuv-dev
dpkg-query -l | grep libwslay-dev
```
Find your dependencies location
```shell
dpkg -L libwslay-dev
```

## Troubleshooting

Somehow in ubuntu, libwslay can't be found by original cmake find_package.<br/>
NvRest work around is adding custom FindWslay.cmake module in ```cmake``` folder

```cmake
find_package(Wslay REQUIRED)
if(NOT WSLAY_FOUND)
    message(FATAL_ERROR "wslay library not found")
endif()
```

This will ensure CMake configuration for H2o found libwslay.so correctly.

