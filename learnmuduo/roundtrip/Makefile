roundtrip : roundtrip.o
	g++ -o roundtrip roundtrip.o -g -L ~/build/debug-install/lib -lmuduo_net -lmuduo_base -lpthread
	rm *.o

roundtrip.o : ./roundtrip.cpp
	g++ -o roundtrip.o -c ./roundtrip.cpp -g -I ~/build/debug-install/include

clean:
	rm *.o roundtrip
