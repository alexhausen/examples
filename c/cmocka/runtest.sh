#!bin/sh

#export PATH in cygwin or LD_LIBRARY_PATH on linux
export CMOCKA_MESSAGE_OUTPUT=XML
export CMOCKA_XML_FILE=result.xml
./test_a