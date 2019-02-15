/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>


/**
 *  get h264/aac from mp4/flv
 *
 * ./test ../media/source.200kbps.768x320.flv
 *
 */
extern int demuxer(int arg0,char** arg1);




int main(int arg0,char** arg1){
   
   demuxer(arg0,arg1);



   return 0;
}
