###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author: Andrew Rozenblit arozen01

# this is needed to have make follow symlinks in dependency lists -- please keep
# it! (but remove this comment)
MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# CalcYouLater: main.o RPNCalc.o parser.o DatumStack.o Datum.o
# 	$(CXX) $(CXXFLAGS) -o main.o RPNCalc.o parser.o DatumStack.o Datum.o

# RPNCalc.o: RPNCalc.cpp 
# 	$(CXX) $(CXXFLAGS) -c MetroSim.cpp 


CalcYouLater: main.o RPNCalc.o DatumStack.o parser.o Datum.o
	$(CXX) $(CXXFLAGS) -o $@ main.o DatumStack.o parser.o Datum.o RPNCalc.o

main.o: main.cpp RPNCalc.h DatumStack.h parser.h Datum.h
	$(CXX) $(CXXFLAGS) -c main.cpp

RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h parser.h Datum.h
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp 

DatumStack.o: DatumStack.h DatumStack.cpp Datum.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

parser.o: parser.h parser.cpp
	$(CXX) $(CXXFLAGS) -c parser.cpp

unit_test: unit_test_driver.o DatumStack.o parser.o Datum.o
	$(CXX) $(CXXFLAGS) $^

##Diff Rules 

if:  
	(./CalcYouLater < if.cylc > if.out) >&ifError.out 
	(./theCalcYouLater < if.cylc > if.gt) >&ifError.gt 
	diff if.out if.gt
	diff ifError.out ifError.gt

exec:  
	(./CalcYouLater < exec.cylc > exec.out) >&execError.out 
	(./theCalcYouLater < exec.cylc > exec.gt) >&execError.gt 
	diff exec.out exec.gt
	diff execError.out execError.gt

fib:  
	(./CalcYouLater < fib.cylc > fib.out) >&fibError.out 
	(./theCalcYouLater < fib.cylc > fib.gt) >&fibError.gt 
	diff fib.out fib.gt
	diff fibError.out fibError.gt

add:  
	(./CalcYouLater < add.cylc > add.out) >&addError.out 
	(./theCalcYouLater < add.cylc > add.gt) >&addError.gt 
	diff add.out add.gt
	diff addError.out addError.gt

fib_debug:  
	(./CalcYouLater < fib_debug.cylc > fib_debug.out) >&fib_debugError.out 
	(./theCalcYouLater < fib_debug.cylc > fib_debug.gt) >&fib_debugError.gt 
	diff fib_debug.out fib_debug.gt
	diff fib_debugError.out fib_debugError.gt

fact:  
	(./CalcYouLater < fact.cylc > fact.out) >&factError.out 
	(./theCalcYouLater < fact.cylc > fact.gt) >&factError.gt 
	diff fact.out fact.gt
	diff factError.out factError.gt

file:  
	(./CalcYouLater < file.cylc > file.out) >&fileError.out 
	(./theCalcYouLater < file.cylc > file.gt) >&fileError.gt 
	diff file.out file.gt
	diff fileError.out fileError.gt

stressTest:
	(./CalcYouLater < stress_test.cylc > stress_test.out) >&stress_testError.out 
	(./theCalcYouLater < stress_test.cylc > stress_test.gt) >&stress_testError.gt 
	diff stress_test.out stress_test.gt
	diff stress_testError.out stress_testError.gt


## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
