add_library(trees BinarySearchTree.h TreeNode.h)

target_include_directories(trees ../include)

add_executable(BinaryTreeSearch main.cpp)

target_link_libraries(BinaryTreeSearch PUBLIC trees)