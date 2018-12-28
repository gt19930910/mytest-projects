/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "openssl/pem.h"
#include "openssl/bio.h"
#include "openssl/evp.h"
#include "openssl/aes.h"

unsigned char key[AES_BLOCK_SIZE] = "123456789abcdef";

#define AES_BITS 10240
#define MSG_LEN 10240

/**********************************************************
函数名：getlen
参数：char *result        --字符串地址
返回值：int                --字符串长度
说明：                    --获取字符串长度
***********************************************************/
int getlen(char *result) {
    int i = 0;
    while (result[i] != '\0') {
        i++;
    }
    return i;
}

/**********************************************************
函数名：aes_encrypt
参数：const char* str_in        --输入字符
参数：unsigned char* key        --key
参数：unsigned char* out        --输出字符
返回值:int                      --0失败  1成功
说明：加密
***********************************************************/
int aes_encrypt(char* str_in, char* out)
{
    if (!str_in || !key || !out) return 0;

    //加密的初始化向量
    unsigned char iv[AES_BLOCK_SIZE];

    //16位密码
    for (int i = 0; i < 16; ++i)
        iv[i] = 0;

    AES_KEY aes;
    if (AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0)
    {
        return 0;
    }

    int len = getlen(str_in);

    AES_cbc_encrypt((unsigned char*)str_in, (unsigned char*)out, len, &aes, iv, AES_ENCRYPT);
    return 1;
}

/**********************************************************
函数名：aes_decrypt
参数：const char* str_in        --输入
参数：unsigned char* key        --key
参数：unsigned char* out        --输出
返回值：int            　　　　　 --0失败  1成功
说明：　　　　　　　　　　　　　　　 --解密
***********************************************************/
int aes_decrypt(char* str_in, char* out)
{
    if (!str_in || !key || !out)
        return 0;

    unsigned char iv[AES_BLOCK_SIZE];//加密的初始化向量
    for (int i = 0; i < 16; ++i)
        iv[i] = 0;

    AES_KEY aes;
    if (AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0)
    {
        return 0;
    }

    int len = getlen(str_in);

    AES_cbc_encrypt((unsigned char*)str_in, (unsigned char*)out, len, &aes, iv, AES_DECRYPT);
    return 1;
}

int base64_encode(char *in_str, int in_len, char *out_str)
{
    BIO *b64, *bio;
    BUF_MEM *bptr = NULL;
    size_t size = 0;

    if (in_str == NULL || out_str == NULL)
        return -1;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, in_str, in_len);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bptr);
    memcpy(out_str, bptr->data, bptr->length);
    out_str[bptr->length] = '\0';
    size = bptr->length;

    BIO_free_all(bio);
    return size;
}

int base64_decode(char *in_str, int in_len, char *out_str)
{
    BIO *b64, *bio;
    BUF_MEM *bptr = NULL;
    int counts;
    int size = 0;

    if (in_str == NULL || out_str == NULL)
        return -1;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    bio = BIO_new_mem_buf(in_str, in_len);
    bio = BIO_push(b64, bio);

    size = BIO_read(bio, out_str, in_len);
    out_str[size] = '\0';

    BIO_free_all(bio);
    return size;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("please input origin str\n");
        return 0;
    } else
    {
        printf("origin-str:%s\n", argv[1]);
    }

    char aes_encode_out[30] = {0};
    aes_encrypt(argv[1], aes_encode_out);
    printf("aes_encode_out:%s\n", aes_encode_out);

    char base64_encode_out[1024] = {0};
    base64_encode(aes_encode_out, strlen(aes_encode_out), base64_encode_out);
    printf("base64_encode_out:%s\n", base64_encode_out);

    char base64_decode_out[1024] = {0};
    base64_decode(base64_encode_out, strlen(base64_encode_out), base64_decode_out);
    printf("base64_decode_out:%s\n", base64_decode_out);

    char aes_decode_out[30] = {0};
    aes_decrypt(base64_decode_out, aes_decode_out);
    printf("aes_decode_out:%s\n", aes_decode_out);
    return 0;
}
