from distutils.core import setup, Extension 

module1 = Extension(
    'test',
    include_dirs=["C:/Users/bktor/AppData/Local/Programs/Python/Python38/include"],
    libraries = ['python38'],
    library_dirs=['C:/Users/bktor/AppData/Local/Programs/Python/Python38/libs'],
    sources = ['main.cpp']
)

setup(name = 'test', version = '1.0', 
    ext_modules = [module1])
