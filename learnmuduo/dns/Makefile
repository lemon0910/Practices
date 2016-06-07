dns : Resolver.o dns.o
	g++ -o dns Resolver.o dns.o -g -L ~/build/debug-install/lib -lmuduo_net -lmuduo_base -lmuduo_cdns -lcares -lpthread

Resolver.o : ./Resolver.cc
	g++ -o Resolver.o -c ./Resolver.cc -g -I ~/build/debug-install/include

dns.o : ./dns.cc
	g++ -o dns.o -c ./dns.cc -g -I ~/build/debug-install/include

clean:
	rm *.o dns
