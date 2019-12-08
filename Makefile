all:sample

sample:main.o entryclassfunction.o hashclassfunction.o  
	g++ main.o entryclassfunction.o hashclassfunction.o -o sample

main.o: main.cpp
	g++ -c main.cpp

entryclassfunction.o: entryclassfunction.cpp
	g++ -c entryclassfunction.cpp

hashclassfunction.o: hashclassfunction.cpp
	g++ -c hashclassfunction.cpp

clean:
	rm -f *o sample
