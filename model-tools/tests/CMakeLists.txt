function(b_1_b name)
    add_executable(${name} ${name}.cpp)
    if (USE_CAFFE)
        add_dependencies(${name} ${PROJECT_NAME}_static)
        add_dependencies(${name} ${PROJECT_NAME}_caffe_static)
        TARGET_LINK_LIBRARIES(${name} ${MODEL_TOOLS_LIBRARIES})
    endif (USE_CAFFE)
    
    if (USE_ONNX)
        add_dependencies(${name} ${PROJECT_NAME}_static)
        add_dependencies(${name} ${PROJECT_NAME}_onnx_static)
        TARGET_LINK_LIBRARIES(${name} ${MODEL_TOOLS_LIBRARIES})
    endif (USE_ONNX)
endfunction()

if (USE_CROSS_COMPILE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif(USE_CROSS_COMPILE)

if (USE_CAFFE)
    b_1_b(caffe2bolt)
    b_1_b(test_model_info_check)
endif (USE_CAFFE)
if (USE_ONNX)
    b_1_b(onnx2bolt)
endif (USE_ONNX)
