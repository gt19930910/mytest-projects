

/*     test how to use command line       */

/******************************************
 ***         unistd.h                   ***
 *
 *   extern char* optarg;
 *   int getopt(int argc,char * const argv[ ],const char * optstring);
 *
 * example:  optstring="a:b:cd::e"
 *           对应到命令行就是-a ,-b ,-c ,-d, -e
 *           冒号表示参数，一个冒号就表示这个选项后面必须带有参数
 *              可以和选项连在一起写，也可以用空格隔开，比如-a123 和-a   123
 *           两个冒号表示可以有参数，也可以没有参数，但要注意有参数时，参数与选项之间不能有空格
 *           ./test -a xxx
 *           ./test -b xxx
 *           ./test -c
 *
 *
 * ****************************************/



#include <stdio.h>
#include <unistd.h>

int main(int arg0,char** arg1){
   
    if (arg0 < 2) {
        fprintf(stderr, "useage:\n");
        fprintf(stderr, "   %s [OPTION...]\n", arg1[0]);
        fprintf(stderr, "Options:\n");
        fprintf(stderr, "   -x              xxxxxxxxx\n");
        fprintf(stderr, "   -c              xxxxxxxxx\n");
        fprintf(stderr, "   -s              xxxxxxxxx\n");
        fprintf(stderr, "   -T              xxxxxxxxx\n");
        fprintf(stderr, "   -h              printf help options\n");
        return 1;
    }

    char opt;
    while ((opt = getopt(arg0, arg1, "x:v:c:Ts::")) != -1) {
        switch (opt) {
            case 'x': printf("optarg %c:%s\n",opt,optarg); break;
            case 'v': printf("optarg %c:%s\n",opt,optarg); break;
            case 'g': printf("optarg %c:%s\n",opt,optarg); break;
            case 'T': printf("optarg %c:%s\n",opt,optarg); break;
            case 'c': printf("optarg %c:%s\n",opt,optarg); break;
            case 's': printf("optarg %c:%s\n",opt,optarg); break;
            default : fprintf(stderr, "Unknown option %c\n", opt); break;
        }
    }

   return 0;
}
