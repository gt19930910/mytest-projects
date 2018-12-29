/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include "src/testGlibConfig.h"

int main(int argc, char* argv[]){
   
    /*
     * 使用的时候进入build文件夹,执行  ./test ../src/setting
     * setting文件是配置文件在src目录下
	 */
	if (argc < 2)
	{
		g_print("please input config file path\n");
		return 0;
	}

	TestGlibConfig(argv[1]);
	
	return 0;
}
