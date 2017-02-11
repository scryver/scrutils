import uuid

try:
    string = unicode
except NameError:
    string = str

VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_BUILD = string(uuid.uuid4())

# Create version file from vars (config.h -> include/config.h)
def create_config_header(target, source, env):
     t_name = string(target[0])
     s_name = string(source[0])
     with open(t_name, 'wt') as target_file:
        with open(s_name, 'rt') as source_file:
            f = source_file.read()
        f = f.format(VERSION_MAJOR=VERSION_MAJOR, VERSION_MINOR=VERSION_MINOR,
                     VERSION_BUILD=VERSION_BUILD)
        target_file.write(f)
     return None

AddOption('--prefix',
          dest='prefix',
          default='build',
          nargs=1, type='string',
          action='store',
          metavar='DIR',
          help='installation prefix')

prefix = GetOption('prefix')
if not prefix.startswith('/') and not prefix.startswith('#') and not prefix[1] == ':':
    prefix = '#' + prefix

# Set C++11 standard
env = Environment(CPPFLAGS=['-std=c++11'],
                  PREFIX = prefix)

env['CPPPATH'] = '$PREFIX/include'
env['LIBPATH'] = '$PREFIX/lib'

env.Append(CPPFLAGS=['-fprofile-arcs', '-g', '-Wall', '-ftest-coverage'])
env.Append(LIBS='gcov')

testEnv = env.Clone()
# conf = Configure(env)
# if not conf.CheckLibWithHeader('m', 'math.h', 'c'):
#     print 'Did not find libm.a or m.lib, exiting!'
#     Exit(1)
# env = conf.Finish()

# Test for SFML, OpenGL, GLEW and GLM libraries
env.ParseConfig('pkg-config sfml-all --cflags --libs')
env.ParseConfig('pkg-config gl --cflags --libs')
env.ParseConfig('pkg-config glew --cflags --libs')

config_builder = Builder(action=create_config_header,
                         suffix='.h',
                         src_suffix='.tmpl.h')
env.Append(BUILDERS={'Header': config_builder})
# env.Command('config.h', 'config.tmpl.h', create_config_header)

SConscript(['games/mapping/SConscript'], 'env', variant_dir='build/tmp/mapping')
SConscript(['games/sandbox/SConscript'], 'env', variant_dir='build/tmp/sandbox')
SConscript(['lib/grapher/src/SConscript'], 'env', variant_dir='build/tmp/lib/grapher')
SConscript(['lib/scrogl/SConscript'], 'env', variant_dir='build/tmp/lib/scrogl')

testEnv = SConscript(['vendor/gtest/SConscript'], 'testEnv')
SConscript(['tests/lib/grapher/SConscript'], 'testEnv', variant_dir='build/tmp/test/grapher')
SConscript(['tests/lib/scrogl/SConscript'], 'testEnv', variant_dir='build/tmp/test/scrogl')
