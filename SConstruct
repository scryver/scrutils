from __future__ import print_function

from utility.headers import create_config_header

AddOption('--prefix',
          dest='prefix',
          default='build',
          nargs=1, type='string',
          action='store',
          metavar='DIR',
          help='installation prefix')
AddOption('--build-release',
          dest='build_release',
          default=False,
          action='store_true',
          help='Build will be optimized for release. This will disable coverage if set.')
AddOption('--coverage',
          dest='coverage',
          default=False,
          action='store_true',
          help='Enable gcoverage')
AddOption('--backend',
          dest='backend',
          default='sfml',
          nargs=1, type='string',
          action='store',
          help='Window manager backend (sfml and glfw supported)')


prefix = GetOption('prefix')
if not prefix.startswith('/') and not prefix.startswith('#') and not prefix[1] == ':':
    prefix = '#' + prefix

# Set C++11 standard
env = Environment(CPPFLAGS = ['-std=c++11'],
                  PREFIX = prefix,
                  CPPPATH = '$PREFIX/include',
                  LIBPATH = '$PREFIX/lib')

config_builder = Builder(action=create_config_header,
                         suffix='.h',
                         src_suffix='.tmpl.h')
env.Append(BUILDERS={'Header': config_builder})

build_release = GetOption('build_release')
if build_release:
    env.Append(CPPFLAGS=['-O3'])
else:
    env.Append(CPPFLAGS=['-O0', '-g', '-Wall', '-Werror'])

    coverage = GetOption('coverage')
    if coverage:
        env.Append(CPPFLAGS=['-fprofile-arcs', '-ftest-coverage'])  # -fno-exceptions
        env.Append(LIBS='gcov')

# conf = Configure(env)
# if not conf.CheckLibWithHeader('m', 'math.h', 'c'):
#     print 'Did not find libm.a or m.lib, exiting!'
#     Exit(1)
# env = conf.Finish()

# Test for SFML, OpenGL, GLEW and GLM libraries
# env.ParseConfig('pkg-config sfml-all --cflags --libs')
# env.ParseConfig('pkg-config gl --cflags --libs')
# env.ParseConfig('pkg-config glew --cflags --libs')

# These need to be set/overwritten by configs
# env['VERSION_MAJOR'] = 'x'
# env['VERSION_MINOR'] = 'y'

backend = GetOption('backend')

if backend == 'glfw':
    env.ParseConfig('pkg-config glfw3 --cflags --libs')
elif backend == 'sfml':
    env.ParseConfig('pkg-config sfml-window --cflags --libs')
else:
    print("Backend '{}' not supported!".format(backend))
    Exit(1)

env.ParseConfig('pkg-config gl --cflags --libs')
env.ParseConfig('pkg-config glew --cflags --libs')

if backend == 'glfw':
    env['USING_BACKEND'] = 'glfw'
    env.Append(CPPDEFINES=['USING_GLFW'])
else:
    env['USING_BACKEND'] = 'sfml'
    env.Append(CPPDEFINES=['USING_SFML'])

sub_dirs = [
    'lib/engine',
    'lib/files',
    'lib/inputs',
    'lib/math',
    'lib/timing',
    'lib/utility',
    'games/sandbox',
]

test_dirs = [
    'lib/files',
    'lib/inputs',
    'lib/math',
    'lib/timing',
    'lib/utility',
]

for d in sub_dirs:
    SConscript([d + '/SConscript'], 'env', variant_dir='build/tmp/' + d)

testEnv = SConscript(['test/SConscript'], 'env')
for d in test_dirs:
    SConscript(['test/' + d + '/SConscript'], 'testEnv', variant_dir='build/tmp/test/' + d)
