find_package(Protobuf 3.5.1 REQUIRED)

include_directories(
	${PROTO_DIR}
)

link_directories(
    ${PROTO_DIR}
)

set(target ${PROTO_DIR}/example/example.proto)


get_filename_component(base_name ${target} NAME_WE)
get_filename_component(file_path ${target} DIRECTORY)

add_custom_command(
    OUTPUT ${file_path}/${base_name}.pb.cc ${file_path}/${base_name}.pb.h
    COMMAND qemu-arm -L /usr/arm-linux-gnueabi /usr/arm-linux-gnueabi/bin/protoc --cpp_out=${PROTO_DIR} -I${PROTO_DIR} ${file_path}/${base_name}.proto
    COMMENT "Generating ${base_name}.pb.cc, ${base_name}.pb.h from ${base_name}.proto"
    VERBATIM
)


add_library(
    protobuf-${base_name}
    STATIC
    ${file_path}/${base_name}.pb.cc
)

target_link_libraries(
    protobuf-${base_name}
    protobuf
)

# Install targets
install(
    TARGETS protobuf-${base_name}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)
