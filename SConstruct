import os

# Define build environment
common_env = Environment()
common_env.Append(CPPFLAGS=['-g', '-std=c++11'])#, '-Wall')
common_env.Append(LIBS=['-lboost_system','-lpthread' , '-lboost_thread'])
common_env.Append(LIBPATH=['/lib','/usr/lib','/usr/local/lib', '/usr/local/boost_1_57_0'])
common_env.Append(CPPPATH=['/lib','/usr/lib','/usr/local/lib', '/usr/local/boost_1_57_0','#/include'])

# Support method
import os.path

def filtered_glob(env, pattern, omit=[], ondisk=True, source=False, strings=False):
    return filter(lambda f: os.path.basename(f.path) not in omit,env.Glob(pattern))

common_env.AddMethod(filtered_glob, "FilteredGlob");

# Clone common library environment
common_lib_env = common_env.Clone()

# Link network library
common_env.Append(LIBS=['-lnetwork'])
common_env.Append(LIBPATH=['#/build/debug/network'])

# Release build is derived from the common build environment
release_env = common_env.Clone()
release_env.Append(CPPDEFINES=['RELEASE'])
release_env.VariantDir('build/release', 'src')

# Debug build is derived from the common build environment
debug_env = common_env.Clone()
debug_env.Append(CPPDEFINES=['DEBUG'])
debug_env.VariantDir('build/debug', 'src')

# Library release build is derived from the common library build environment
release_lib_env = common_env.Clone()
release_lib_env.Append(CPPDEFINES=['RELEASE'])
release_lib_env.VariantDir('build/release/', 'src')

# Library debug build is derived from the common library build environment
debug_lib_env = common_env.Clone()
debug_lib_env.Append(CPPDEFINES=['DEBUG'])
debug_lib_env.VariantDir('build/debug/', 'src')

# Defining modules to build
modules = ['generator_app', 'filter_app', 'comparator_app']
lib_modules = ['network']

# Now that all build environment have been defined, let's iterate over
# them and invoke the lower level SConscript files.
for mode, envs in dict(debug=[debug_lib_env, debug_env]).iteritems(): #release=[release_lib_env, release_env]
    print '###Libraries###'
    libs = envs[0].SConscript('build'+ os.sep + mode + os.sep + 'SConscript', {'env': envs[0], 'modules': lib_modules}, duplicate=0)
    print '###Applications###' 
    apps = envs[1].SConscript('build'+ os.sep + mode + os.sep + 'SConscript', {'env': envs[1], 'modules': modules}, duplicate=0)
    for app in apps:
        for lib in libs:
            Depends(app, lib)


