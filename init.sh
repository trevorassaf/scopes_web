#!/bin/bash

pushd $(dirname ${BASH_SOURCE[0]}) > /dev/null

# Initialize user-data directories
rm -rf files > /dev/null
mkdir files
mkdir files/basic_videos
mkdir files/edited_videos

chown -R www-data files

# Initialize db
pushd sql/ > /dev/null
mysql -u trevor -ppassword -e "source refresh_db.sql;"
popd > /dev/null

# Insert initial db data 
hhvm hhvm/init/init_db.hh $(pwd)

popd > /dev/null
