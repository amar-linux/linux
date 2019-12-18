dlopen()

If, at the time that the program was started, the environment variable LD_LIBRARY_PATH was defined to contain a colon-separated list of directories, then these are searched. (As a security measure this variable is ignored for set-user-ID and set-group-ID programs.)

The function dlopen() loads the dynamic library file named by the null-terminated string filename and returns an opaque "handle" for the dynamic library. If filename is NULL, then the returned handle is for the main program. If filename contains a slash ("/"), then it is interpreted as a (relative or absolute) pathname. Otherwise, the dynamic linker searches for the library as follows (see ld.so(8) for further details):
o
(ELF only) If the executable file for the calling program contains a DT_RPATH tag, and does not contain a DT_RUNPATH tag, then the directories listed in the DT_RPATH tag are searched.

o

If, at the time that the program was started, the environment variable LD_LIBRARY_PATH was defined to contain a colon-separated list of directories, then these are searched. (As a security measure this variable is ignored for set-user-ID and set-group-ID programs.)

o

(ELF only) If the executable file for the calling program contains a DT_RUNPATH tag, then the directories listed in that tag are searched.

o

The cache file /etc/ld.so.cache (maintained by ldconfig(8)) is checked to see whether it contains an entry for filename.

o

The directories /lib and /usr/lib are searched (in that order).


====================================================  IMPORTANT ===========================================


LD_LIBRARY_PATH has to be given while running the programm and cannot be set in the env variable ,
or you can place the shared library in the search path like 

/usr/local/lib
/usr/lib/
......