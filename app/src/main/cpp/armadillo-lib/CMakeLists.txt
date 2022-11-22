set(LIB_DIR "${PROJECT_SOURCE_DIR}/armadillo-lib")
include_directories(${LIB_DIR})
#defined ARMA_DONT_USE_LAPACK
#defined ARMA_DONT_USE_BLAS
add_library(
		armadillo-lib
		"nnw.cpp"
		"${LIB_DIR}/armadillo_bits"
 )
set_target_properties(armadillo-lib PROPERTIES LINKER_LANGUAGE CXX)