/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

/*写入字符串函数*/
ssize_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	strcat(stream, (char *)ptr);
	puts(stream);
	return size*nmemb;
}

/*
//写入文件函数
ssize_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}
*/

/* 
	编译方式 首先安装curl库 gcc test.c -lcurl即可 
	使用时请根据实际情况，填写url和post数据
	GET请求可以不加post数据
	-k参数根据情况选择加与不加
*/

int main(int argc, char *argv[])
{
  	CURL *curl2;
	CURLcode res2;
	//FILE *fp2;
	//struct curl_slist *list=NULL;
	//list=curl_slist_append(list, argv[1]);//这个其实是-H但是这边没用到所以注释
	//list=curl_slist_append(list, argv[2]);//有几个-H头就append几次
	static char str[20480];
	res2 = curl_global_init(CURL_GLOBAL_ALL);
	curl2 = curl_easy_init();
	if(curl2) 
	{
		/*若需要存入文件需要先打开文件*/
		//fp2=fopen("UsefullInfo.json", "w+");

		/*这是请求的url*/
		curl_easy_setopt(curl2, CURLOPT_URL, "https://192.168.112.4:8006/api2/json/access/ticket");

		/*post 数据*/
		curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, "username=root@pam&password=nicaiba_88");

		/*若有-H则需要添加list*/
		//curl_easy_setopt(curl2, CURLOPT_HTTPHEADER, list);

		/*下面两行代表-k参数*/
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYHOST, 0);

		/*调试信息-v*/
		curl_easy_setopt(curl2, CURLOPT_VERBOSE, 1);

		/*拿数据*/
		curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, write_data);

		/*表示将数据输入到字符串中*/
		curl_easy_setopt(curl2, CURLOPT_WRITEDATA, str);

		/*将数据存入文件*/
		//curl_easy_setopt(curl2, CURLOPT_WRITEDATA, fp2);

		/*执行请求*/
		res2 = curl_easy_perform(curl2);
		curl_easy_cleanup(curl2);
		//fclose(fp2);
	}
	curl_global_cleanup();
	return 0;
}
