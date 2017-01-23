set(HEADERS
    stdafx.h
	Blob.h
    Common.h
    ISerializable.h
    PolymorphSerializable.h
    SerializerBase.h
    Serializer.h
    DeserializerBase.h
    Deserializer.h
)

set(SOURCES
    stdafx.cpp
	Blob.cpp
    SerializerBase.cpp
    Serializer.cpp
    DeserializerBase.cpp
    Deserializer.cpp
)

include_directories(
    ${Boost_INCLUDE_DIRS}
    .
    ../.
)

source_group("Sources" FILES ${SOURCES})
source_group("Headers" FILES ${HEADERS})

set(PROJECT_CONTENT ${SOURCES} ${HEADERS})

add_library(SerializationLib ${PROJECT_CONTENT})
