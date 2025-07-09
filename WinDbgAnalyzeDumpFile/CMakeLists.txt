cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("WinDbgAnalyzeDumpFile")

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# 设置PDB文件输出目录
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/pdb)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/pdb)

# 将源代码添加到此项目的可执行文件。
add_executable (WinDbgAnalyzeDumpFile "main.cpp" readme.md)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WinDbgAnalyzeDumpFile PROPERTY CXX_STANDARD 20)
endif()

# 确保生成PDB文件
if(MSVC)
    target_compile_options(WinDbgAnalyzeDumpFile PRIVATE /Zi)
    set_target_properties(WinDbgAnalyzeDumpFile PROPERTIES 
        LINK_FLAGS "/DEBUG /PDB:${CMAKE_PDB_OUTPUT_DIRECTORY}/${PROJECT_NAME}.pdb"
    )
endif()