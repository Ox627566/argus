cli11 = dependency('CLI11')

libs = declare_dependency(
    dependencies: [cli11],
    include_directories: include_directories('.')
)
sources  = files(
    'argus.cpp'
)
executable(
    'argus',
    'main.cpp',
    sources,
    dependencies: libs,
    cpp_args: ['-include', 'pch.hpp'],
)
