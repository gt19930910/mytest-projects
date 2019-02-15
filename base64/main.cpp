/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "CBase64Tool.h"

#include <malloc.h>
#include <string.h>
#include <iostream>

int main(int argc,char** argv){
    
     CBase64Tool base64;

    string zw("月亮代表我的心");
    //string zw("yueliangda-=##$ibiaowo de xin");
    
    int len = zw.length();

    char * p = (char*)malloc(len+1);
    memset( p, 0, len+1 );
    memcpy( p,zw.c_str(), len );
    //string src = "abcd1234ABCD+-*/";

    string src( p,len );
    cout << "len:"<< src.length() << ",src:" << src.c_str() << endl;
    
    //编码
    string res = base64.Base64Encode( src );
    cout << "2base64->encode   :" << res.c_str( ) << endl;
    //解码
    string res2 = base64.Base64Decode( res );
    cout << "2base64->decode   :" << res2.c_str( ) << endl;
    
    return 0;
}

