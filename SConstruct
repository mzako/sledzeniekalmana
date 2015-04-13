import os

# Define build environment
common_env = Environment()
common_env.Append(CPPFLAGS=['-std=c++11'])
common_env.Append(CPPPATH=['/lib','/usr/lib','/usr/local/lib', '/usr/local/boost_1_57_0'])

# Support method
import os.path

def filtered_glob(env, pattern, omit=[], ondisk=True, source=False, strings=False):
    return filter(lambda f: os.path.basename(f.path) not in omit,env.Glob(pattern))

common_env.AddMethod(filtered_glob, "FilteredGlob");

# Release build is derived from the common build environment
release_env = common_env.Clone()
release_env.Append(CPPDEFINES=['RELEASE'])
release_env.VariantDir('build/release', 'src')

# Debug build is derived from the common build environment
debug_env = common_env.Clone()
debug_env.Append(CPPDEFINES=['DEBUG'])
debug_env.VariantDir('build/debug', 'src')

# Defining modules to build
modules = ['generator_app', 'filter_app', 'comparator_app']

# Now that all build environment have been defined, let's iterate over
# them and invoke the lower level SConscript files.
for mode, env in dict(release=release_env, debug=debug_env).iteritems():
    env.SConscript('build'+ os.sep + mode + os.sep + 'SConscript', {'env': env, 'modules': modules}, dupicate=0)