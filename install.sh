
if [ ! -d ../database ]; then
    git clone git@gitlab.com:hackerexecute/database.git
    cd database/
    make all
else
    make all
fi
