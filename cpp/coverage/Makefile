cov:
	g++ -o cov --coverage -fPIC -O0 cov.cpp

clean:
	rm -fr cov cov.gcda cov.gcno report1 report2

report1: cov.gcda
	mkdir -p report1
	lcov -c -d . -o report1/coverage.info
	genhtml -t "Coverage test" --highlight --legend --num-spaces 4 -o report1/ report1/coverage.info

report2:
	mkdir -p report2
	~/Software/gcovr-3.1/scripts/gcovr --root=. --html --html-details --exclude-unreachable-branches --sort-uncovered --output=report2/report.html
	#~/Software/gcovr-3.1/scripts/gcovr --root=. --xml --output=report2/gcovr.report.xml --sort-uncovered
