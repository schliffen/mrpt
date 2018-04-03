# Check for system jpeglib:
# ===================================================
SET(CMAKE_MRPT_HAS_JPEG 1)	# Always present: system or built-in
IF(MSVC OR APPLE)
	SET(CMAKE_MRPT_HAS_JPEG_SYSTEM 0)
ELSE(MSVC OR APPLE)
	FIND_PACKAGE(JPEG)
	IF(JPEG_FOUND)
		#MESSAGE(STATUS "Found library: jpeg  - Include: ${JPEG_INCLUDE_DIR}")
		INCLUDE_DIRECTORIES("${JPEG_INCLUDE_DIR}")

		SET(CMAKE_MRPT_HAS_JPEG_SYSTEM 1)
	ELSE(JPEG_FOUND)
		SET(CMAKE_MRPT_HAS_JPEG_SYSTEM 0)
	ENDIF(JPEG_FOUND)
ENDIF(MSVC OR APPLE)

IF(NOT CMAKE_MRPT_HAS_JPEG_SYSTEM)
	# Include embedded version headers:
	include(ExternalProject)
	# download Eigen from bitbucket
	ExternalProject_Add(JPEG
		URL               "https://github.com/libjpeg-turbo/libjpeg-turbo/archive/1.5.90.tar.gz"
		URL_MD5           "85f7f9c377b70cbf48e61726097d4efa"
		SOURCE_DIR        "${MRPT_BINARY_DIR}/otherlibs/libjpeg-turbo/"
		CMAKE_ARGS
			-DENABLE_SHARED=OFF
			-DCMAKE_POSITION_INDEPENDENT_CODE=ON
		INSTALL_COMMAND   ""
	)

	SET(JPEG_INCLUDE_DIRS
		"${MRPT_BINARY_DIR}/otherlibs/libjpeg-turbo/"
		"${MRPT_BINARY_DIR}/JPEG-prefix/src/JPEG-build")
	SET(JPEG_LIBRARIES ${MRPT_BINARY_DIR}/JPEG-prefix/src/JPEG-build/${CMAKE_STATIC_LIBRARY_PREFIX}jpeg${CMAKE_STATIC_LIBRARY_SUFFIX})

	INCLUDE_DIRECTORIES("${JPEG_INCLUDE_DIRS}")
ENDIF(NOT CMAKE_MRPT_HAS_JPEG_SYSTEM)
