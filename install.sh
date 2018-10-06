
# Create needed directories
mkdir build
mkdir lib
mkdir tests/build

# Compile and link library
make all
make clean

# Install use of library in cygwin environment
usrlib=/usr/lib/
usrinc=/usr/include/

echo "\nCopying lib/libdatabase.a to C++ lib path"
cp -f lib/libdatabase.a $usrlib

if [! -f lib/libdatabase.a]; then
    echo "\nInstallation failed.\n"
    exit 1
fi

echo "\nCopying header files to C++ include path"
cp -f include/*.h $usrinc

echo "\nInstallation success."
