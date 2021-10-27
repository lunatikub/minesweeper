project(
  'algo',
  'c',
  default_options : [
    'c_std=gnu11',
  ]
)

c_compiler = meson.get_compiler('c')
root_dir = meson.source_root()

flags = c_compiler.get_supported_arguments(
  [
    '-Wall',
    '-Werror',
    '-D_GNU_SOURCE',
    '-Wunused',
    '-Wunused-value',
    '-Wunused-variable',
    '-Wunused-parameter',
    '-Wbool-compare',
    '-Wformat-security',
    '-Winit-self',
    '-Wlogical-op',
    '-Wtrampolines',
    '-Wmissing-format-attribute',
    '-Wno-error=deprecated-declarations',
    '-Wno-format-zero-length',
    '-Wshadow',
    '-Wmissing-declarations',
    '-Wpointer-arith',
    '-Wformat=2',
    '-pipe',
    '-g3',
    '-pthread',
  ]
)

inc = include_directories('include')
test_inc = include_directories('tests')

# List of modules.
modules = [
  'solver',
]

# Add sources and tests for each module.
foreach module : modules
  subdir('src/' + module)
endforeach

# Has to be done after the first previous loop in order
# to manage circular dependencies.
foreach module: modules
  subdir('tests/' + module)
endforeach
