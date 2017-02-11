import os
import sys
import subprocess


def google_test_init(env):
    gtestBuildDir = env.Dir('#vendor/googletest/build')
    gtestInstallDir = env.Dir('#vendor')
    incPath = env.Dir('#vendor/include')
    libPath = env.Dir('#vendor/lib')

    if not gtestBuildDir.exists():
        os.mkdir(gtestBuildDir.get_abspath())

    if env.Dir('#vendor/include/gtest').exists() \
            and env.Dir('#vendor/include/gmock').exists():
        return incPath, libPath

    cmakeCmd = subprocess.Popen(['cmake',
                                 '-DCMAKE_INSTALL_PREFIX={}'.format(gtestInstallDir.get_abspath()),
                                 '..'],
                                cwd=gtestBuildDir.get_abspath())
    out, err = cmakeCmd.communicate()
    if err:
        print('GoogleTest::CMake Error::{}'.format(err))
        sys.exit(1)

    makeCmd = subprocess.Popen(['make'], cwd=gtestBuildDir.get_abspath())
    out, err = makeCmd.communicate()
    if err:
        print('GoogleTest::Make Error::{}'.format(err))
        sys.exit(1)

    installCmd = subprocess.Popen(['make', 'install'], cwd=gtestBuildDir.get_abspath())
    out, err = installCmd.communicate()
    if err:
        print('GoogleTest::Install Error::{}'.format(err))
        sys.exit(1)

    return incPath, libPath
