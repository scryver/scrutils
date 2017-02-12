import os
import uuid

try:
    string = unicode
except NameError:
    string = str

VERSION_BUILD = string(uuid.uuid4())

# Create version file from vars (config.h -> include/config.h)
def create_config_header(target, source, env):
    assert 'VERSION_MAJOR' in env
    assert 'VERSION_MINOR' in env

    major = env['VERSION_MAJOR']
    minor = env['VERSION_MINOR']

    t_name = string(target[0])
    s_name = string(source[0])
    with open(t_name, 'wt') as target_file:
       with open(s_name, 'rt') as source_file:
           f = source_file.read()
       f = f.format(VERSION_MAJOR=major, VERSION_MINOR=minor,
                    VERSION_BUILD=VERSION_BUILD)
       target_file.write(f)
    return None


def install_headers(env, libname, files, implementations=None):
    for filename in files:
        fs = filename.split(os.path.sep)
        fs[-1] = fs[-1].rstrip('.hpp')
        for i, f in enumerate(fs):
            if '_' in f:
                fs[i] = f.replace('_', ' ')
            fs[i] = fs[i].title().replace(' ', '')
        name = '$PREFIX/include/{}/{}.hpp'.format(libname, os.path.sep.join(fs))
        env.InstallAs(name, filename)

    if implementations:
        for filename in implementations:
            fs = filename.split(os.path.sep)
            fs = [f.title() for f in fs[:-1]] + [fs[-1]]
            name = '$PREFIX/include/{}/{}'.format(libname, os.path.sep.join(fs))
            env.InstallAs(name, filename)
