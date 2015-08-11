#!/bin/bash

cd sql/
mysql -u trevor -ppassword -e "source refresh_db.sql;"
cd ../
