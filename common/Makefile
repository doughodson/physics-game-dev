
all: testVector testMatrix3x3 testQuaternion

testVector: testVector.cpp
	g++ -std=c++11 testVector.cpp -o testVector -I.

testMatrix3x3: testMatrix3x3.cpp
	g++ -std=c++11 testMatrix3x3.cpp -o testMatrix3x3 -I.

testQuaternion: testQuaternion.cpp
	g++ -std=c++11 testQuaternion.cpp -o testQuaternion -I.

clean:
	rm -f testVector
	rm -f testMatrix3x3
	rm -f testQuaternion
	
