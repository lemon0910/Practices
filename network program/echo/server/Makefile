server : echo.o main.o
	g++ -o server echo.o main.o -g -I ../../../build/debug-install/include -L ../../../build/debug-install/lib -lmuduo_net -lmuduo_base -lpthread
	rm *.o

echo.o : ./echo.cc
	g++ -o echo.o -c -g ./echo.cc -I ../../../build/debug-install/include

main.o : ./main.cc
	g++ -o main.o -c -g ./main.cc -I ../../../build/debug-install/include

clean : 
	rm server *.o
