
# Create needed directories
if [ ! -d build ]; then
    mkdir build
fi

if [ ! -d lib ]; then
    mkdir lib
fi

if [ ! -d tests/build ]; then
    mkdir tests/build
fi
echo ""

# Compile and link library
make all
make clean

# Install use of library in cygwin environment
usrlib=/usr/lib/
usrinc=/usr/include/

echo ""
echo "Copying library to C++ lib path"

if [ -d $usrlib ]; then
    cp -f lib/libdatabase.a $usrlib
else
    echo "Unable to copy lib/libdatabase.a to C++ library path."
fi

echo ""
echo "Copying header files to C++ include path"

if [ -d $usrinc ]; then
    cp -f include/*.h $usrinc
fi
