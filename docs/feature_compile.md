# NvServ Features & Build Options

On your CMake you have to set options to which NvServ features do you want use.<br/>
By design is recommended to be one server type (REST/GRPC/TCP/UDP) per executable.<br/>

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

## Complete NvServ CMake Options
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
|15| NVSERV_FEATURE_VM_V8 | nvserv::vm_v8 | PLAN | V8 Engine integration for server side HTML or JS executions |

## NvServ Library Options
NvServ has options to choose engine for certain library, currently the options are available for

|#|FEATURES| ENGINE OPTIONS | LIBRARY | DESCRIPTION |
|--|--------|----------------|---------|------------|
| 1| NVSERV_SERVER_REST | NVSERV_JSON_USE_RAPIDJSON | rapidjson | NvServ will use rapidjson as backend engine for json serializer and deserializer. |
|  |  | NV_REST_JSON_USE_NJSON | nlohman-json  | NvServ will use nlohman json as backend engine for json serializer and deserializer. |
| 2| NVSERV_FATURE_API_CLIENT | NVSERV_JSON_USE_RAPIDJSON | rapidjson | NvServ will use rapidjson as backend engine for json serializer and deserializer. |
| |  | NV_REST_JSON_USE_NJSON | nlohman-json  | NvServ will use nlohman jon as backend engine for json serializer and deserializer. |

### 