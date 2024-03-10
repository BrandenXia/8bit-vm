project('8bit-vm', 'c',
    version : '0.1.0',
    license : 'MIT',
    default_options : ['warning_level=3', 'werror=true', 'c_std=c11', 'build_type=debugoptimized']
)

inc = [include_directories('include')]

subdir('src')

dep_libs = [
    vm_lib,
    compiler_lib,
]

executable('vm',
    main_source,
    include_directories : inc,
    link_with : dep_libs
)
