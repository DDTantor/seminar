add_executable("seminar" seminar.cc seminar.ini FEM.hh driver.hh bctype.hh)
target_link_dune_default_libraries("seminar")

dune_symlink_to_source_files(FILES seminar.ini)
dune_symlink_to_source_files(FILES circle.msh)
