
repo = database

if [ ! -d ../$repo ]; then
    git clone git@gitlab.com:hackerexecute/database.git
    cd $repo
    make all
else
    make all
fi
