/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>


#include <glib.h>
#include <gtk/gtk.h>

#include "src/spice-obj.h"

#include "header.h"

#include "src/vcd-msg-box.h"

static  void spice_created(SpiceObj* obj,int width,int height,gpointer data,gpointer user_priv){
    LOGD("spice_created w:%d,h:%d,data:%p",width,height,data);
}


void testGobject(){
  //  gtk_init(0,0);

   SpiceObj* so = g_object_new(SPICE_TYPE_OBJ, NULL);


   LOGD("connect 'spice-created'");
   g_signal_connect(so,"spice-created",G_CALLBACK(spice_created),so);

   //
   emit_spice_created(so);

   //g_object_ref(so);
}

int main(int arg0,char** arg1){
   
#if 0
        //1.gtk环境初始化
        gtk_init(&arg0, &arg1);
 
        //2.创建一个窗口
        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
        //3.创建一个固定布局容器fixed
        GtkWidget *fixed = gtk_fixed_new();
        //将fixed添加到window中
        gtk_container_add(GTK_CONTAINER(window), fixed);
 
        //4.创建一个button按钮
        GtkWidget *button1 = gtk_button_new_with_label("button1");
        //将button1添加到固定容器fixed中
        gtk_fixed_put(GTK_FIXED(fixed), button1, 0,0);
 
        GtkWidget *button2 = gtk_button_new_with_label("button2");
        //将button1添加到固定容器fixed中
        gtk_fixed_put(GTK_FIXED(fixed), button2, 0, 0);
 
        //5.移动button2到(150,150)的位置
        gtk_fixed_move(GTK_FIXED(fixed), button2, 150, 150);
 
        //6.设置button2的大小
        gtk_widget_set_size_request(button2,100, 50);
 
        //7.显示所有窗口
        gtk_widget_show_all(window);
 
        //8.主事件循环
        gtk_main();
#elif 0
        testGobject();
#else 1
        gtk_init(&arg0, &arg1);
        message_box("sfasgasfwef");
        gtk_main();
#endif


   return 0;
}
