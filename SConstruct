import os

# Define build environment
common_env = Environment()
common_env.Append(CPPFLAGS=['-g', '-std=c++11'])#, '-Wall')
common_env.Append(LIBS=['-lboost_system','-lpthread' , '-lboost_thread', '-lclient_server'])
common_env.Append(LIBPATH=['#/build/debug/client_server','/lib','/usr/lib','/usr/local/lib', '/usr/local/boost_1_57_0'])
common_env.Append(CPPPATH=['/lib','/usr/lib','/usr/local/lib', '/usr/local/boost_1_57_0','#/include'])

# Support method
import os.path

def filtered_glob(env, pattern, omit=[], ondisk=True, source=False, strings=False):
    return filter(lambda f: os.path.basename(f.path) not in omit,env.Glob(pattern))

common_env.AddMethod(filtered_glob, "FilteredGlob");


lib_env = common_env.Clone()
lib_env.VariantDir('client_server', 'src')

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
lib_modules = ['client_server']

# Now that all build environment have been defined, let's iterate over
# them and invoke the lower level SConscript files.
for mode, env in dict(debug=debug_env).iteritems(): #release=release_env, 
    env.SConscript('build'+ os.sep + mode + os.sep + 'SConscript', {'env': env, 'modules': modules, 'env_lib': lib_env, 'lib_modules': lib_modules}, dupicate=0)


