project(
    'myproject',#название проекта
    'cpp',#язык
    version:'0.1.0',#версия кода
    meson_version:'>=0.46',#минимально поддерживаемая версия Meson
    default_options: ['cpp_std=c++11']#используемый стандарт C++
    )
    #src =include_directories('.')
    subdir('src')

doxyfile =configuration_data()#ключ-значение
doxyfile.set('OUTPUT_DIRECTORY',meson.build_root())
configure_file(input:'Doxyfile', output:'Doxyfile',configuration: doxyfile)#создание файла из шаблона
doxygen =find_program('doxygen')
if doxygen.found()#ninja doc генерирует документацию
    run_target('doc', command: [doxygen,join_paths(meson.build_root(),'Doxyfile')])
endif