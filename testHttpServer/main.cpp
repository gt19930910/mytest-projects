/*
 * http_server_test.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: liao
 */



#include <sstream>
#include <cstdlib>
#include <iostream>


#include "httpserver/json/json.h"
using namespace std;
#include "httpserver/http_server.h"

//接口     http://172.18.12.121:9000/hello    
void hello(Request &request, Json::Value &root) {
	root["hello"] = "world";
}

//接口     http://172.18.12.121:9000/sayhello?name=fengfeng&age=27
void sayhello(Request &request, Json::Value &root) {
	std::string name = request.get_param("name");
	std::string age = request.get_param("age");

	root["name"] = name;
	root["age"] = atoi(age.c_str());
}

void login(Request &request, Json::Value &root) {
	std::string name = request.get_param("name");
	std::string pwd = request.get_param("pwd");

	LOG_DEBUG("login user which name:%s, pwd:%s", name.c_str(), pwd.c_str());
	root["code"] = 0;
	root["msg"] = "login success!";
}

void usleep(Request &request, Response &response) {
    Json::Value root;
    std::string sleep_time = request.get_param("usleep");
    if (sleep_time.empty()) {
        root["msg"] = "usleep is empty!";
        response.set_body(root);
        return;
    }
   // usleep(atoi(sleep_time.c_str()));
    root["code"] = 0;
    root["msg"] = "success!";
    response.set_body(root);
}

void test_schedule() {
    LOG_INFO("START schedule ....");
}

void livestart(Request &request, Json::Value &root) {
    cout << "livestart" << endl;
    root["hello"] = "livestart";
}
void liveend(Request &request, Json::Value &root) {
    cout << "liveend" << endl;
    root["hello"] = "liveend";
}

/*
cdn回调接口
//流开始回调
http://live.audiocn.org:8020/cdn/livestart
//流结束回调
http://live.audiocn.org:8020/cdn/liveend
*/

int main(int argc, char **args) {

    //1. 创建  HttpServer
    HttpServer http_server;

    //2. 添加接口,默认 get 
    http_server.add_mapping("/hello", hello);
//	http_server.add_mapping("/usleep", usleep);
//	http_server.add_mapping("/sayhello", sayhello);
//	http_server.add_mapping("/login", login, POST_METHOD);
    //http_server.set_schedule(test_schedule);

    http_server.add_mapping("/cdn/livestart", livestart);
    http_server.add_mapping("/cdn/liveend", liveend);

    int port = 8080;
    int backlog = 100000;
    int max_events = 1000;

    cout << "main start" << endl;
    //3. 启动服务器
    http_server.start(port, backlog, max_events);
    return 0;
}

