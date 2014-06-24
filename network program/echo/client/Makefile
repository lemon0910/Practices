client : client.o
	g++ -o client client.o -g -I ../../../build/debug-install/include -L ../../../build/debug-install/lib -lmuduo_net -lmuduo_base -lpthread
	rm *.o

client.o : ./client.cc
	g++ -o client.o -c -g ./client.cc -I ../../../build/debug-install/include

clean : 
	rm client *.o
