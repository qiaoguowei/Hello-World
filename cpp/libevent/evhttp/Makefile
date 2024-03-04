exec : main.cpp EvhttpServer.cpp
	g++ -o $@ $^ -I/home/qgw/SDK/boost_1_73_0 -L/home/qgw/SDK/boost_1_73_0/stage/lib  -levent -lboost_filesystem -lboost_thread -pthread

clean:
	rm exec
