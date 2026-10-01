# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-src")
  file(MAKE_DIRECTORY "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-build"
  "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-subbuild/faker-cxx-populate-prefix"
  "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-subbuild/faker-cxx-populate-prefix/tmp"
  "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-subbuild/faker-cxx-populate-prefix/src/faker-cxx-populate-stamp"
  "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-subbuild/faker-cxx-populate-prefix/src"
  "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-subbuild/faker-cxx-populate-prefix/src/faker-cxx-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-subbuild/faker-cxx-populate-prefix/src/faker-cxx-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/ferna/Documents/Caline/GitHub/APS/Projeto-algoritmos-de-ordenacao-de-dados/build/_deps/faker-cxx-subbuild/faker-cxx-populate-prefix/src/faker-cxx-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
