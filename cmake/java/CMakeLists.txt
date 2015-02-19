cmake_minimum_required(VERSION 2.8)

find_package(Java REQUIRED)
include(UseJava)
project(java_test)

add_jar(hello
	SOURCES A.java
	ENTRY_POINT A
	)

#ENTRY_POINT requires cmake version 3.0