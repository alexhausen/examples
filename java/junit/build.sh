#!/bin/bash
unset _JAVA_OPTIONS
javac -d bin src/pkg/Klass.java
javac -d bin -cp bin:lib/junit-4.12.jar test/pkg/KlassTest.java
java -cp bin:lib/junit-4.12.jar:lib/hamcrest-core-1.3.jar org.junit.runner.JUnitCore pkg.KlassTest