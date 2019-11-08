
#include <glib.h>
#include <gtk/gtk.h>

#define VCD_PIC_PATH "/Volumes/feng-sd/code-back/share-projects/testGObject/img/"

void set_css(GtkWidget *widget, const gchar *data_css)
{
    GtkCssProvider *provider = gtk_css_provider_new ();
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_css_provider_load_from_data(provider, data_css, -1, NULL);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

void set_img(GtkWidget *win, const char *widget_class, const char *pic_name)
{
    char css_string[500];
    char path[100];
    snprintf(path, sizeof(path), VCD_PIC_PATH"%s", pic_name);
    snprintf(css_string,sizeof(css_string), "%s{background-image:url('%s')}", widget_class, path);
    set_css(win, css_string);
}


void message_box(const char *information)
{
    GtkWidget *label, *label_pic, *window_message_box, *btn_ok, *fix, *scrolled_win;
    window_message_box = gtk_window_new(GTK_WINDOW_TOPLEVEL); //GTK_WINDOW_POPUP
    gtk_window_set_modal((GtkWindow *)window_message_box, TRUE);
    gtk_window_set_keep_above(GTK_WINDOW(window_message_box), TRUE);
    gtk_window_set_position(GTK_WINDOW(window_message_box), GTK_WIN_POS_CENTER_ALWAYS);//居中
    gtk_container_set_border_width(GTK_CONTAINER(window_message_box), 50);
    gtk_window_set_decorated(GTK_WINDOW(window_message_box), TRUE);//无边框

//    fix = gtk_fixed_new();

//    char tmp_info[120];
//    snprintf(tmp_info,sizeof(tmp_info),"%s", information);
//    label = gtk_label_new(tmp_info);

//    btn_ok = gtk_button_new_with_label("关闭 1");
//    gtk_button_set_relief(GTK_BUTTON(btn_ok), GTK_RELIEF_NONE);
//    gtk_widget_set_size_request(btn_ok, 150, 0);

//    label_pic = gtk_label_new("");
//    gtk_widget_set_size_request(label_pic, 70, 70);

//    scrolled_win  = gtk_scrolled_window_new(NULL, NULL);
//    gtk_widget_set_size_request(scrolled_win, 250, 0);
//    gtk_container_add(GTK_CONTAINER(scrolled_win), label);

//    gtk_fixed_put((GtkFixed *)fix, label_pic, 85, 20);
//    gtk_fixed_put((GtkFixed *)fix, scrolled_win, 0, 100);
//    gtk_fixed_put((GtkFixed *)fix, btn_ok, 50, 155);

//    gtk_container_add(GTK_CONTAINER(window_message_box), fix);

//    g_signal_connect_swapped(G_OBJECT(btn_ok), "clicked", G_CALLBACK(gtk_widget_destroy), window_message_box);


     //set_img(label_pic, "label", "gantanhao.png");
//     set_css(window_message_box, "window{border-radius:0px;background-color: rgb(230, 230, 230)}");
     set_css(window_message_box, "window{border-radius:2px;background-color: rgb(256, 256, 0)}");
    // set_css(btn_ok, "button{color: white;background: rgb(53, 126, 169);border: 1px solid rgb(40, 94, 142);border-radius: 0px}");
     //set_css(btn_ok, "button:hover{border-radius:0px;background: #3070a9}");

    gtk_widget_show_all(window_message_box);
}

