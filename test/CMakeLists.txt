add_executable(testMeshData MeshDataTest.cpp)
add_executable(testTiff TiffTest.cpp)
add_executable(testAPR APRTest.cpp)

target_link_libraries(testMeshData ${GTEST_LIBRARIES} libapr)
target_link_libraries(testTiff ${GTEST_LIBRARIES} libapr)
target_link_libraries(testAPR ${GTEST_LIBRARIES} libapr)
