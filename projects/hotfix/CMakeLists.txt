add_library(bug1 SHARED bug1.cc)
add_library(bug2 SHARED bug2.cc)

add_executable(project_hotfix main.cc hotfix.cc)
# 设置安装路径
install(TARGETS project_hotfix DESTINATION hotfix)
install(TARGETS bug1 bug2 DESTINATION hotfix)