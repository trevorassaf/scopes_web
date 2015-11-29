#!/bin/bash

pushd $(dirname ${BASH_SOURCE[0]}) > /dev/null

# Initialize db
pushd sql/ > /dev/null
mysql -u trevor -ppassword -e "source refresh_db.sql;"
popd > /dev/null

# Insert initial db data 
hhvm hhvm/init/init_db.hh

popd > /dev/null
