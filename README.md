# logg
A repository to help organize all the code written since the last commit in August
and to host future code. The fundamental directories are: 
	-core
	-alg
	-include, which has two sub directories core and alg
For each new module, you should use the setupdir.sh bash script 
(remember to run chmod +x setupdir.sh to make it executable)

This script will create a directory inside either core or alg,
with the following structure:
	-src
	-lib
	-bin
	-doc
along with a custom Makefile, to compile any src file in src, to
an object file in lib subdirectory. In the future, extra functionality
such as merging these .o files to an .a file may be added. The bin file
is there for the sake of writing test programs to test the module's
functions. Furthermore, include files will be stored in the directory

include/core/(module name) or
include/alg/(module name)
