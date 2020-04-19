
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "FileWriter.h"
#include "Queue.h"
#include "QueueMonitor.h"
#include "Compressor.h"
#include "Writer.h"
#include "FileReaderMonitor.h"

#include <mutex>
#include <condition_variable>
#include <thread>
#include <stdlib.h>
#include <time.h>

TEST_CASE( "ALOT File Test") {

	int x = system("rm cmpalot cmplargenum cmponeblk cmppad cmpzeroblk");
	x++;
	srand((unsigned int)clock());
	int threads_amount = rand()%6 + 1;
	unsigned int elements = rand()%15 + 1;
	FileReaderMonitor file_h("alot");
	FileWriter* file_w = new FileWriter("cmpalot");
	std::vector<QueueMonitor*> queues(threads_amount);
	std::vector<Compressor*> comps(threads_amount);
	std::vector<std::thread*> threads(threads_amount);
	for (int i = 0; i < threads_amount; ++i) {
		queues[i] = new QueueMonitor(elements);
		comps[i] = new Compressor(4, file_h, *queues[i], threads_amount, i+1);
		threads[i] = new std::thread(&Compressor::compress, std::ref(*comps[i]));
	}
	Writer writer(*file_w, queues);
	writer.write();
	for (int i = 0; i < threads_amount; ++i) {
		(*threads[i]).join();
		delete threads[i];
		delete queues[i];
		delete comps[i];
	}
	delete file_w;
    REQUIRE( !system("diff alot4.out cmpalot") );
}

TEST_CASE( "LARGENUM File Test") {
	int threads_amount = rand()%6 + 1;
	unsigned int elements = rand()%15 + 1;
	FileReaderMonitor file_h("largenum");
	FileWriter* file_w = new FileWriter("cmplargenum");
	std::vector<QueueMonitor*> queues(threads_amount);
	std::vector<Compressor*> comps(threads_amount);
	std::vector<std::thread*> threads(threads_amount);
	for (int i = 0; i < threads_amount; ++i) {
		queues[i] = new QueueMonitor(elements);
		comps[i] = new Compressor(4, file_h, *queues[i], threads_amount, i+1);
		threads[i] = new std::thread(&Compressor::compress, std::ref(*comps[i]));
	}
	Writer writer(*file_w, queues);
	writer.write();
	for (int i = 0; i < threads_amount; ++i) {
		(*threads[i]).join();
		delete threads[i];
		delete queues[i];
		delete comps[i];
	}
	delete file_w;
    REQUIRE( !system("diff largenum4.out cmplargenum") );
}

TEST_CASE( "ONEBLK File Test") {
	int threads_amount = rand()%6 + 1;
	unsigned int elements = rand()%15 + 1;
	FileReaderMonitor file_h("oneblk");
	FileWriter* file_w = new FileWriter("cmponeblk");
	std::vector<QueueMonitor*> queues(threads_amount);
	std::vector<Compressor*> comps(threads_amount);
	std::vector<std::thread*> threads(threads_amount);
	for (int i = 0; i < threads_amount; ++i) {
		queues[i] = new QueueMonitor(elements);
		comps[i] = new Compressor(4, file_h, *queues[i], threads_amount, i+1);
		threads[i] = new std::thread(&Compressor::compress, std::ref(*comps[i]));
	}
	Writer writer(*file_w, queues);
	writer.write();
	for (int i = 0; i < threads_amount; ++i) {
		(*threads[i]).join();
		delete threads[i];
		delete queues[i];
		delete comps[i];
	}
	delete file_w;
    REQUIRE( !system("diff oneblk4.out cmponeblk") );
}

TEST_CASE( "PAD File Test") {
	int threads_amount = rand()%6 + 1;
	unsigned int elements = rand()%15 + 1;
	FileReaderMonitor file_h("pad");
	FileWriter* file_w = new FileWriter("cmppad");
	std::vector<QueueMonitor*> queues(threads_amount);
	std::vector<Compressor*> comps(threads_amount);
	std::vector<std::thread*> threads(threads_amount);
	for (int i = 0; i < threads_amount; ++i) {
		queues[i] = new QueueMonitor(elements);
		comps[i] = new Compressor(8, file_h, *queues[i], threads_amount, i+1);
		threads[i] = new std::thread(&Compressor::compress, std::ref(*comps[i]));
	}
	Writer writer(*file_w, queues);
	writer.write();
	for (int i = 0; i < threads_amount; ++i) {
		(*threads[i]).join();
		delete threads[i];
		delete queues[i];
		delete comps[i];
	}
	delete file_w;
    REQUIRE( !system("diff pad8.out cmppad") );
}

TEST_CASE( "ZEROBLK File Test") {
	int threads_amount = rand()%6 + 1;
	unsigned int elements = rand()%15 + 1;
	FileReaderMonitor file_h("zeroblk");
	FileWriter* file_w = new FileWriter("cmpzeroblk");
	std::vector<QueueMonitor*> queues(threads_amount);
	std::vector<Compressor*> comps(threads_amount);
	std::vector<std::thread*> threads(threads_amount);
	for (int i = 0; i < threads_amount; ++i) {
		queues[i] = new QueueMonitor(elements);
		comps[i] = new Compressor(3, file_h, *queues[i], threads_amount, i+1);
		threads[i] = new std::thread(&Compressor::compress, std::ref(*comps[i]));
	}
	Writer writer(*file_w, queues);
	writer.write();
	for (int i = 0; i < threads_amount; ++i) {
		(*threads[i]).join();
		delete threads[i];
		delete queues[i];
		delete comps[i];
	}
	delete file_w;
    REQUIRE( !system("diff zeroblk3.out cmpzeroblk") );
}


