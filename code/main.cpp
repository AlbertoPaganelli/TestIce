/***************************************************************************

 begin : Sep 23 2013

 copyright : (C) 2001 Alberto Paganelli

 email : 61825@studenti.unimore.it

 ***************************************************************************/

/***************************************************************************

 * *

 * This program is free software for non commercial purpose *

 * and for public research institutes; you can redistribute it and/or *

 * modify it under the terms of the GNU General Public License. *

 * For commercial purpose see appropriate license terms *

 * *

 ***************************************************************************/

#include <Freeze/Freeze.h>
#include "DemoMaps.h"
#include <iostream>
#include <ctime>
#include "mac_clock_gettime.h"

#define CYCLE 1000

using namespace std;

/// A Ice communicator
Ice::CommunicatorPtr communicator;

/// A Connection with a BDB database
Freeze::ConnectionPtr connection;

/// A utility variable
Ice::Int i;

/// The struct used to get the time
struct timespec start, stop;

/// Returns the difference between two times.
/// \param[in] clock1 The stop time.
/// \param[in] clock2 The start time.
/// \return the difference between the two times
double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=1000*(diffticks)/(CLOCKS_PER_SEC);
    return diffms;
}

/// Write and read on BDB a ByteSeqMap
void WriteReadByteSeqMap() {
	//Byte Map
	ByteMap byteMap(connection,"ByteSeqMap");
	byteMap.clear();
	Demo::ByteSeq byteSeq;

	byteSeq.clear();
	for (int j = 0; j < Demo::ByteSeqSize; j++)
	{
		byteSeq.push_back((Ice::Byte)(i%256));
	}

	clock_gettime(CLOCK_MONOTONIC, &start);


	for (i = 0; i < CYCLE; i++)
	{
		byteMap.insert(make_pair(i,byteSeq));
	}

	clock_gettime(CLOCK_MONOTONIC, &stop);

	//std::cout << diffclock(end,begin)/CYCLE << " ms/write" << std::endl;
	cout << (float) ((Demo::ByteSeqSize * CYCLE)/timediff(start, stop)) / 1000000 << " MB/s" << endl;
	cout << timediff(start, stop) << endl;

	ByteMap::iterator p;

	clock_gettime(CLOCK_MONOTONIC, &start);

	for (p = byteMap.begin(); p != byteMap.end(); ++p){
		Demo::ByteSeq bs = p->second;
		//std::cout << p->first << "\t" << p->second.i << "\t" << p->second.j << "\t" << p->second.d << "\t" << std::endl;
	}

	clock_gettime(CLOCK_MONOTONIC, &stop);

	//std::cout << diffclock(end,begin)/CYCLE << " ms/read" << std::endl;
	cout << (float) ((Demo::ByteSeqSize * CYCLE)/timediff(start, stop)) / 1000000 << " MB/s" << endl;
	cout << timediff(start, stop) << endl;

}

/// Write and read on BDB a StringSeqMap
void WriteReadStringSeqMap() {
	//Byte Map
	StringMap stringMap(connection,"StringSeqMap");
	stringMap.clear();
	string s;
	Demo::StringSeq stringSeq;

	stringSeq.clear();
	for (int j = 0; j < Demo::StringSeqSize; j++)
	{
		stringSeq.push_back("aaaa");
	}

	clock_gettime(CLOCK_MONOTONIC, &start);

	for (i = 0; i < CYCLE; i++)
	{
		stringMap.insert(make_pair(i,stringSeq));
	}

	clock_gettime(CLOCK_MONOTONIC, &stop);

	//std::cout << diffclock(end,start)/CYCLE << " ms/write" << std::endl;
	cout << (float) ((Demo::StringSeqSize * CYCLE * 4)/timediff(start, stop)) / 1000000 << " MB/s" << endl;
	cout << timediff(start, stop) << endl;

	StringMap::iterator p;

	clock_gettime(CLOCK_MONOTONIC, &start);

	for (p = stringMap.begin(); p != stringMap.end(); ++p){
		Demo::StringSeq ss = p->second;
		//std::cout << p->first << "\t" << p->second.i << "\t" << p->second.j << "\t" << p->second.d << "\t" << std::endl;
	}

	clock_gettime(CLOCK_MONOTONIC, &stop);

	//std::cout << diffclock(end,start)/CYCLE << " ms/read" << std::endl;
	cout << (float) ((Demo::StringSeqSize * CYCLE * 4)/timediff(start, stop)) / 1000000 << " MB/s" << endl;
	cout << timediff(start, stop) << endl;

}

/// Write and read on BDB a FixedMap
void WriteReadFixedMap() {
	 // Instantiate the byte map.
    //
	FixedMap map(connection, "FixedMap");
    //StringIntMap map(connection, "simple");

    // Clear the map.
    //
    map.clear();
	Ice::Int a,b;
	Ice::Double c;
	FixedMap::iterator p;
	Demo::Fixed fixed;
    //StringIntMap::iterator p;

	a = (Ice::Int)std::rand() % 1001;
	b = (Ice::Int)std::rand() % 1001;
	c = (Ice::Double)((std::rand() % 1000)/1000.0);
	fixed.i = a;
	fixed.j = b;
	fixed.d = c;

	clock_gettime(CLOCK_MONOTONIC, &start);

    // Populate the map.
    //
	for (i = 0; i < CYCLE; i++) {
		map.insert(std::make_pair(i,fixed));
    }

	clock_gettime(CLOCK_MONOTONIC, &stop);

	//std::cout << diffclock(end,start)/CYCLE << " ms/write" << std::endl;
	cout << (float) ((CYCLE * (2*sizeof(Ice::Int) + sizeof(Ice::Double)))/timediff(start, stop)) / 1000000 << " MB/s" << endl;
	cout << timediff(start, stop) << endl;

    // Iterate over the map and change the values.
    //
	clock_gettime(CLOCK_MONOTONIC, &start);

    for (p = map.begin(); p != map.end(); ++p)
		Demo::Fixed f = p->second;
		//std::cout << p->first << "\t" << p->second.i << "\t" << p->second.j << "\t" << p->second.d << "\t" << std::endl;

    clock_gettime(CLOCK_MONOTONIC, &stop);

	//std::cout << diffclock(end,start)/CYCLE << " ms/read" << std::endl;
    cout << (float) ((CYCLE * (2*sizeof(Ice::Int) + sizeof(Ice::Double)))/timediff(start, stop)) / 1000000 << " MB/s" << endl;
    cout << timediff(start, stop) << endl;
}

/// Write and read on BDB a StringDoubleMap
void WriteReadStringDoubleMap() {
	//Byte Map
	StringDoubleMap stringDoubleMap(connection,"StringDoubleMap");
	stringDoubleMap.clear();
	Demo::StringDouble stringDouble;

	stringDouble.s="aaaaa";
	stringDouble.d = (Ice::Double)1.0;

	clock_gettime(CLOCK_MONOTONIC, &start);

	for (i = 0; i < CYCLE; i++)
	{
		stringDoubleMap.insert(make_pair(i,stringDouble));
	}

	clock_gettime(CLOCK_MONOTONIC, &stop);

	//std::cout << diffclock(end,start)/CYCLE << " ms/write" << std::endl;
	cout << (float) ((CYCLE * (5 + sizeof(Ice::Double)))/timediff(start, stop)) / 1000000 << " MB/s" << endl;
	cout << timediff(start, stop) << endl;

	StringDoubleMap::iterator p;

	clock_gettime(CLOCK_MONOTONIC, &start);

	for (p = stringDoubleMap.begin(); p != stringDoubleMap.end(); ++p){
		Demo::StringDouble sd = p->second;
		//std::cout << p->first << "\t" << p->second.i << "\t" << p->second.j << "\t" << p->second.d << "\t" << std::endl;
	}

	clock_gettime(CLOCK_MONOTONIC, &stop);

	//std::cout << diffclock(end,start)/CYCLE << " ms/read" << std::endl;
	cout << (float) ((CYCLE * (5 + sizeof(Ice::Double)))/timediff(start, stop)) / 1000000 << " MB/s" << endl;
	cout << timediff(start, stop) << endl;
}

int main(int argc, char* argv[])
{
    // Initialize the Communicator.
    //
    communicator = Ice::initialize(argc, argv);

    // Create a Freeze database connection.
    //
	connection = Freeze::createConnection(communicator, "db");
	
	cout << "Byte Sequence" << endl;
	WriteReadByteSeqMap();
	cout << "String Sequence" << endl;
	WriteReadStringSeqMap();
	cout << "String Double" << endl;
	WriteReadStringDoubleMap();
	cout << "Fixed" << endl;
	WriteReadFixedMap();

    //// Find and erase the last element.
    ////
    //p = map.find("z");
    //assert(p != map.end());
    //map.erase(p);

    // Clean up.
    //
    connection->close();
    communicator->destroy();

	cout << "\nPremi un tasto per uscire...." << endl;
	getchar();

	return 0;
}
