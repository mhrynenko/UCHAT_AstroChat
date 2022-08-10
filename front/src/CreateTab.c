#include "../inc/GUI_headeR.h"

void CreateTab(char* name, int groupid) {
    for (int i = 0; i<=groupcount; i++){
        if(grouparr[i].chatroomid == groupid) return;
    }
    char **names = mx_strsplit(name, '-');
    while(*names) {
        if(strcmp(*names, user_info.user_name) != 0) {
            mx_strdel(&name);
            name = strdup(*names);
            break;
        }
        names++;
    }

    grouparr[groupcount].chatroomname = g_strdup_printf ("%s", name);
    grouparr[groupcount].chatroomid = groupid;
    grouparr[groupcount].row = 0;
    grouparr[groupcount].ChatBox  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    grouparr[groupcount].editflag = -1;

    GtkWidget *new_chat_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 1);

    GtkWidget *text_and_send_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *text_view_scrolledWindow = gtk_scrolled_window_new(NULL,NULL);
    grouparr[groupcount].TextField = gtk_text_view_new();
    g_signal_connect(G_OBJECT(grouparr[groupcount].TextField), "focus-in-event", G_CALLBACK(on_messgae_text_view_focus_in_event), NULL);
    g_signal_connect(G_OBJECT(grouparr[groupcount].TextField), "focus-out-event", G_CALLBACK(on_messgae_text_view_focus_out_event), NULL);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(grouparr[groupcount].TextField), GTK_WRAP_WORD_CHAR);
    gtk_container_add (GTK_CONTAINER(text_view_scrolledWindow), grouparr[groupcount].TextField);
    add_css_style_by_name(GTK_WIDGET(grouparr[groupcount].TextField), "textview_focus_out");

    grouparr[groupcount].SendButton = gtk_button_new();/////
    gtk_widget_set_focus_on_click(GTK_WIDGET(grouparr[groupcount].SendButton), FALSE);
    g_signal_connect(G_OBJECT(grouparr[groupcount].SendButton), "clicked", G_CALLBACK(send_button_clicked), &grouparr[groupcount]);
    gtk_widget_set_size_request (grouparr[groupcount].SendButton, 50, 50);
    add_css_style_by_name(GTK_WIDGET(grouparr[groupcount].SendButton), "send_message_button");
    //g_signal_connect(G_OBJECT(grouparr[groupcount].TextField), "activate", G_CALLBACK(on_textfield_activate), &grouparr[groupcount].SendButton;
    gtk_box_pack_start (GTK_BOX(text_and_send_box), text_view_scrolledWindow, 1, 1, 0);
    gtk_box_pack_start (GTK_BOX(text_and_send_box), grouparr[groupcount].SendButton, 0, 0, 0);

    grouparr[groupcount].ChatScrolledWondow = gtk_scrolled_window_new(NULL,NULL);
    gtk_container_add (GTK_CONTAINER(grouparr[groupcount].ChatScrolledWondow), grouparr[groupcount].ChatBox);

    gtk_box_pack_start (GTK_BOX(new_chat_box), grouparr[groupcount].ChatScrolledWondow, 1, 1, 0);
    gtk_box_pack_start (GTK_BOX(new_chat_box), text_and_send_box, 0, 0, 0);

    gtk_stack_add_named(GTK_STACK(chat_stack), GTK_WIDGET(new_chat_box), mx_itoa(grouparr[groupcount].chatroomid));


    GtkWidget* event_box = gtk_event_box_new();
    grouparr[groupcount].ChatButton = gtk_button_new_with_label(grouparr[groupcount].chatroomname);
    gtk_widget_set_name(GTK_WIDGET(grouparr[groupcount].ChatButton), mx_itoa(grouparr[groupcount].chatroomid));
    gtk_widget_set_size_request(GTK_WIDGET(grouparr[groupcount].ChatButton), -1, 40);
    gtk_container_add (GTK_CONTAINER (event_box), grouparr[groupcount].ChatButton);



    gtk_box_pack_start(GTK_BOX(chatname_buttons_box), event_box, 0, 0, 0);
    g_signal_connect (G_OBJECT(event_box), "button_press_event", G_CALLBACK(right_click_on_chat_button), &grouparr[groupcount]);
    g_signal_connect(G_OBJECT(grouparr[groupcount].ChatButton), "clicked", G_CALLBACK(chatname_button_clicked), NULL);
    add_css_style(grouparr[groupcount].ChatButton);

    gtk_widget_show_all(chat_window);
    groupcount++;
    mx_strdel(&name);
}
