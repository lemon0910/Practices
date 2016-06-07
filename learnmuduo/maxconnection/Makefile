echo : echo.o main.o
	g++ -o echo echo.o main.o -g -L ~/build/debug-install/lib -lmuduo_net -lmuduo_base -lpthread

echo.o : ./echo.cc
	g++ -o echo.o -c ./echo.cc -g -I ~/build/debug-install/include

main.o : ./main.cc
	g++ -o main.o -c ./main.cc -g -I ~/build/debug-install/include

clean:
	rm *.o echo
