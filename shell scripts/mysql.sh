#!/bin/sh
for((i=0;i<8;i++));
do
    mysql -pmysql -e"use c_t_store;select * from Block_Table_$i";
done
