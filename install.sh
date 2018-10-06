
# Create needed directories
mkdir build
mkdir lib
mkdir tests/build

# Compile and link library
make all
make clean

# Install use of library in cygwin environment
usrlib = /usr/lib/
usrinc = /usr/include/

echo ""
echo "Copying lib/libdatabase.a to C++ lib path"
cp -f lib/libdatabase.a $usrlib

echo ""
echo "Copying header files to C++ include path"
cp -f include/*.h $usrinc

echo ""
echo "Install success."
