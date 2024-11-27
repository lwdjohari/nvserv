# NvServ
Lightweight Server Development Framework (REST,SOCKET,GRPC) for C++17.

> [!WARNING]
> Status : WIP, Experimental & Unstable.  


# NvServ Features & Build Options

On your CMake you have to set options to which NvServ features do you want use.<br/>
By design is recommended to be one server type (REST/GRPC/SCOKET) per executable.<br/>

### Create REST API Server Development
Develop REST API Server, using postgresql database and have HTTP client to connect to other remote API endpoints.

```cmake
# REST API Server Development
set(NVSERV_SERVER_REST ON)
set(NVSERV_SERVER_GRPC ON)
set(NVSERV_SERVER_SOCKET ON)

# Turn on features postgres db & API Client
set(NVSERV_FEATURE_POSTGRES ON)
set(NVSERV_FEATURE_API_CLIENT ON)

# Use rapidjson as the json serdes engine
set(NVSERV_JSON_USE_RAPIDJSON ON)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME}  
    nvserv::core 
    nvserv::socket
    nvserv::storage
    nvserv::rest
    nvserv::postgres
    nvserver::grpc
    nvserv::apiclient
    nvserv::server
    )
```

## NvServ CMake Features & Options
|#|FEATURES| LIBRARY | STATUS |DESCRIPTION|
|--|-------|-----|----|----------|
| 1| - | nvserv::core | WIP | NvServ Core |
| 2| NVSERV_SERVER_REST | nvserv::rest | WIP | REST API & Server-side server development. ~~H2O as underlying HttpServer engine.~~ Working on HTTP Server replacement. |
| 3| NVSERV_SERVER_GRPC | nvserv::grpc | WIP | GRPC Server, encapsulate and abstracting Google C++ Grpc lib for standardize and lower boilerplate when developing GRPC Server. |
| 4| NVSERV_SERVER_SOCKET | nvserv::socket | WIP | TCP/UDP Server development. Currently planning to use ~~H20~~ standalone ASIO socket as underlying. |
| 5| NVSERV_FEATURE_POSTGRES | nvserv::postgres | WIP | [Nvql Universal Datalayer](https://github.com/lwdjohari/nvql/) for postgresql database (transport binary protocol impl).  |
| 6| NVSERV_FEATURE_ORACLE | nvserv::oracle | WIP | [Nvql Universal Datalayer](https://github.com/lwdjohari/nvql/) for oracle database (transport binary protocol impl). |
| 7| NVSERV_FEATURE_MYSQL | nvserv::mysql | PLAN | Datalayer for MYSQL compatible database. |
| 8| NVSERV_FEATURE_SQLITE | nvserv::sqlite | PLAN | Datalayer for SQLITE database. |
| 9| NVSERV_FEATURE_REDIS | nvserv::redis | PLAN | Redis integration. |
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
This framework trying to not use any shared lib to made dependencies management easier.

- Removed H2O, currently working on the H2O Webserver replacement for the Http Webserver

## Static Dependecies
- [nvcore](https://github.com/lwdjohari/nvcore)
- [nvql](https://github.com/lwdjohari/nvql)
- [nvlog](https://github.com/lwdjohari/nvlog)
- Google protobuf
- Google gRpc
- Google Abseil-cpp
- BoringSSL
- Standalone ASIO

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
