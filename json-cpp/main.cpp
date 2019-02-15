/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/*    README
 *   use opencode https://github.com/open-source-parsers/jsoncpp.git
 *
 *   1. git clone 
 *   2. cd jsoncpp 
 *      python amalgamate.py
 *      //copy dist/ to your project
*/


#include <json/json.h>

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace Json;


/*
  array:
  value["andy"].append( "123" );  
  value["andy"].append( "true" );

  Json::Value val_array = value["andy"];  
  int iSize = val_array.size(); 


*/

string makeJsonObject(){
    Json::Value user;
    user["userId"] = 61393656;
    user["roomId"] = 590242;
    user["nickName"] = "昵称";
    
    cout<< "测试创建json字符串:"<<user.toStyledString()<<endl;
    
    return user.toStyledString();
}

void parseJsonString(){
    
    string str = makeJsonObject();
    
    cout << "需要解析的字符串:"<<str<<endl;
    
    Json::Reader reader;
    Json::Value value;
    if ( reader.parse( str, value ) ) {
        cout << "parse ok!" << endl;
          
         if ( !value["userId"].isNull( ) ) {
            cout << "userId   !isNull()" << endl;
            int userId = value["userId"].asInt();
            cout << "userId:" << userId <<  endl;
          }
          
         if ( !value["nickName"].isNull( ) ) {
            string str = value["nickName"].asString( );
            cout << "nickName   !isNull()" << endl;
            cout << str.c_str( ) << endl;
         }
          
         if ( !value["test"].isNull( ) ) {
            string str = value["test"].asString( );
            cout << "test   !isNull2()" << endl;
            cout << str.c_str( ) << endl;
            cout << str.length( ) << endl;
         }else{
              cout << "test  == isNull2() 没有这个字段"<<endl;
         }
    }
}

int main(int argc,char** argv){
    
    // create json object
    makeJsonObject();
    
    // parse json object
    parseJsonString();
    
    return 0;
}
