timer2 : timer2.o
	g++ -o timer2 timer2.o -g -L ~/build/debug-install/lib -lmuduo_net -lmuduo_base -lpthread
	rm *.o

timer2.o : ./timer2.cpp
	g++ -o timer2.o -c ./timer2.cpp -g -I ~/build/debug-install/include

clean:
	rm *.o timer2
