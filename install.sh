
# Create needed directories
mkdir build
mkdir lib
mkdir tests/build

# Compile and link library
make all
make clean
make tclean

# Install use of library in cygwin environment
usrlib = /usr/lib/
usrinc = /usr/include/

echo "Copying lib/libdatabase.a to C++ lib path\n"
cp -f lib/libdatabase.a $usrlib

echo "Copying header files to C++ include path\n"
cp -f include/*.h $usrinc

echo "\nInstall completed"
