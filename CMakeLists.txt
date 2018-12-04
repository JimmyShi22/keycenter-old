#------------------------------------------------------------------------------
# Top-level CMake file for FISCO-BCOS.
# ------------------------------------------------------------------------------
# This file is part of FISCO-BCOS.
#
# FISCO-BCOS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# FISCO-BCOS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with FISCO-BCOS.  If not, see <http://www.gnu.org/licenses/>
#
# (c) 2016-2018 fisco-dev contributors.
#------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.4)
set(CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_DIR})

project(KeyCenter VERSION "2.0")

add_compile_options(-std=c++11)

# install dependencies
include(EthBuildInfo)
include(ProjectMHD)
include(ProjectCryptopp)
include(ProjectJsonCpp)
include(ProjectJsonRpcCpp)
include(ProjectBoost)

add_subdirectory(libdevcore)
add_subdirectory(libdevcrypto)

# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

include_directories(${MHD_INCLUDE_DIR})
include_directories(${JSONCPP_INCLUDE_DIR})
include_directories(${JSONRPCCPP_INCLUDE_DIR})


# 指定生成目标
set(EXE_NAME "keycenter")
add_executable(${EXE_NAME} ${DIR_SRCS})
# 添加链接库
target_link_libraries(${EXE_NAME} ${Boost_LIBRARIES})
target_link_libraries(${EXE_NAME} boost_system)
target_link_libraries(${EXE_NAME} JsonRpcCpp::Common)
target_link_libraries(${EXE_NAME} JsonRpcCpp::Client)
target_link_libraries(${EXE_NAME} JsonRpcCpp::Server)
target_link_libraries(${EXE_NAME} stdc++)





