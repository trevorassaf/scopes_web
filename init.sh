#!/bin/bash

# Initialize db
cd sql/
mysql -u trevor -ppassword -e "source refresh_db.sql;"
cd ../

# Insert initial db data 
hhvm hhvm/init/init_db.hh
