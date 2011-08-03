#!/bin/sh
for i in {1..5000}
do
   echo "COUNT: $i"
   ./test_engine_core_no_cppunit
done
