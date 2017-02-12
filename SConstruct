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
        env.Append(CPPFLAGS=['-fprofile-arcs', '-ftest-coverage'])
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


SConscript(['lib/inputs/SConscript'], 'env', variant_dir='build/tmp/lib/inputs')
SConscript(['lib/math/SConscript'], 'env', variant_dir='build/tmp/lib/math')
SConscript(['lib/utility/SConscript'], 'env', variant_dir='build/tmp/lib/utility')
SConscript(['games/sandbox/SConscript'], 'env', variant_dir='build/tmp/games/sandbox')

testEnv = SConscript(['test/SConscript'], 'env')
SConscript(['test/lib/inputs/SConscript'], 'testEnv', variant_dir='build/tmp/test/lib/inputs')
SConscript(['test/lib/math/SConscript'], 'testEnv', variant_dir='build/tmp/test/lib/math')
SConscript(['test/lib/utility/SConscript'], 'testEnv', variant_dir='build/tmp/test/lib/utility')
