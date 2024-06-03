# NvServ
Lightweight Server Development Framework (REST,SOCKET,GRPC) for C++17.<br/> 
\[Plan for backward compat to C++14]

> [!WARNING]
> Currently compatibility with C++14 is not yet throughly tested.<br/>
> Status : WIP, Experimental & Unstable.  

# Development & Dependencies

NvServ use h2o proven http1.1/http2 webserver as the underlying http server.

# NvServ Features & Build Options

On your CMake you have to set options to which NvServ features do you want use.<br/>
By design is recommended to be one server type (REST/GRPC/SCOKET) per executable.<br/>

### Create REST API Server Development
Develop REST API Server, using postgresql database and have HTTP client to connect to other remote API endpoints.

```cmake
# REST API Server Development
set(NVSERV_SERVER_REST ON)

# Turn on features postgres db & API Client
set(NVSERV_FEATURE_POSTGRES ON)
set(NVSERV_FEATURE_API_CLIENT ON)

# Use nlohman json as the json serdes engine
set(NVSERV_JSON_USE_NJSON ON)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME}  
    nvserv::core 
    nvserv::rest
    nvserv::postgres
    nvserv::apiclient
    )
```

## NvServ CMake Features & Options
|#|FEATURES| LIBRARY | STATUS |DESCRIPTION|
|--|-------|-----|----|----------|
| 1| - | nvserv::core | WIP | NvServ Core |
| 2| NVSERV_SERVER_REST | nvserv::rest | WIP | REST API & Server-side server development. H2O as underlying HttpServer engine. |
| 3| NVSERV_SERVER_GRPC | nvserv::grpc | PLAN | GRPC Server, encapsulate and abstracting Google C++ Grpc lib for standardize and lower boilerplate when developing GRPC Server. |
| 4| NVSERV_SERVER_SOCKET | nvserv::socket | PLAN | TCP/UDP Server development. Currently planning to use H20 socket as underlying. |
| 5| NVSERV_FEATURE_POSTGRES | nvserv::postgres | WIP | Datalayer for postgresql database (transport binary protocol impl).  |
| 6| NVSERV_FEATURE_ORACLE | nvserv::oracle | WIP | Datalayer for oracle database (transport binary protocol impl). |
| 7| NVSERV_FEATURE_MYSQL | nvserv::mysql | PLAN | Datalayer for MYSQL compatible database. |
| 8| NVSERV_FEATURE_SQLITE | nvserv::sqlite | PLAN | Datalayer for SQLITE database. |
| 9| NVSERV_FEATURE_REDIS | nvserv::redis | PLAN | TCP/UDP Server development. |
|10| NVSERV_FEATURE_S3 | nvserv::s3 | PLAN | S3 Integrations. |
|11| NVSERV_FEATURE_ENVOY | nvserv::envoy | WIP | Envoy dataplane integration. |
|12| NVSERV_FEATURE_API_CLIENT | nvserv::apiclient | WIP | HTTP Client for consuming web page or REST API. |
|13| NVSERV_FEATURE_GRPC_CLIENT | nvserv::grpcclient | PLAN | GRPC Client for grpc services. |
|14| NVSERV_FEATURE_MQTT_CLIENT | nvserv::mqttclient | PLAN | MQTT Client for connecting to MQTT Broker. |

## NvServ Library Options
NvServ has options to choose engine for certain library, currently the options are available for
- Json: if not specified will use nlohman-json as default
  
|#|FEATURES| ENGINE OPTIONS | LIBRARY | DESCRIPTION |
|--|--------|----------------|---------|------------|
| 1| NVSERV_SERVER_REST | NVSERV_JSON_USE_RAPIDJSON | rapidjson | NvServ will use rapidjson as backend engine for json serializer and deserializer. |
|  |  | NV_REST_JSON_USE_NJSON | nlohman-json  | NvServ will use nlohman json as backend engine for json serializer and deserializer. |
| 2| NVSERV_FATURE_API_CLIENT | NVSERV_JSON_USE_RAPIDJSON | rapidjson | NvServ will use rapidjson as backend engine for json serializer and deserializer. |
| |  | NV_REST_JSON_USE_NJSON | nlohman-json  | NvServ will use nlohman jon as backend engine for json serializer and deserializer. |

## Development
- CMake 3.10
- C++14/C++17 compiler

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

### Checking your shared-lib
In linux you can check for already installed shared library by executing this command
```shell
dpkg-query -l | grep libuv-dev
dpkg-query -l | grep libwslay-dev
```
Find your dependencies location
```shell
dpkg -L libwslay-dev
```

### Troubleshooting

Somehow in ubuntu, libwslay can't be found by original cmake find_package.<br/>
NvServ work around is adding custom FindWslay.cmake module in ```cmake``` folder

```cmake
find_package(Wslay REQUIRED)
if(NOT WSLAY_FOUND)
    message(FATAL_ERROR "wslay library not found")
endif()
```

This will ensure CMake configuration for H2o found libwslay.so correctly.



## Contributions

Currently we are still on-going roadmap design and architectural design that might be lead to complete rewrite or complete breaking changes.
We might accept contributors when everything above have better & crytal-clears roadmap.

## License

Copyright [2024] [Linggawasistha Djohari]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
