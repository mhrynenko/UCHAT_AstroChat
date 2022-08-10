#include "../inc/GUI_headeR.h"

void delete_message(int groupid, int msgid){
    //looking for room id
    int temp_gropindex = 0;
    while(grouparr[temp_gropindex].chatroomid != groupid && temp_gropindex!= 101){
        temp_gropindex++;
    }
    if(grouparr[temp_gropindex].chatroomid != groupid) return;
    //looking for msg
    int temp_msgindex = 0;
    while(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].msgid != msgid && temp_msgindex!= 128){
        temp_msgindex++;
    }
    if(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].msgid != msgid) return;
    gtk_container_remove(GTK_CONTAINER(grouparr[temp_gropindex].ChatBox), 
                        grouparr[temp_gropindex].RoomsMsg[temp_msgindex].msg_and_name_box);
    grouparr[temp_gropindex].row--;
    gtk_widget_show_all(GTK_WIDGET(chat_stack));
}

void edit_message(int groupid, int msgid, char* newtext){
    //looking for room id
    int temp_gropindex = 0;
    while(grouparr[temp_gropindex].chatroomid != groupid && temp_gropindex!= 101){
        temp_gropindex++;
    }
    if(grouparr[temp_gropindex].chatroomid != groupid) return;
    //looking for msg
    int temp_msgindex = 0;
    while(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].msgid != msgid && temp_gropindex!= 500){
        temp_msgindex++;
    }
    if(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].msgid != msgid) return;
        add_css_style_by_name(GTK_WIDGET(grouparr[temp_gropindex].TextField), "textview_focus_in");  
        add_css_style_by_name(GTK_WIDGET(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].msg_label), "message_label_right"); 
        //if(strcmp(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].text,newtext) != 0) {
        gchar* new_gtext = newtext;
        if(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].is_edited == 0){
        sprintf(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].timetext, "%s(ed.)", grouparr[temp_gropindex].RoomsMsg[temp_msgindex].timetext);
        gtk_label_set_text (GTK_LABEL(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].time_label), grouparr[temp_gropindex].RoomsMsg[temp_msgindex].timetext);
        grouparr[temp_gropindex].RoomsMsg[temp_msgindex].is_edited = 1;
    }
    //grouparr[temp_gropindex].RoomsMsg[temp_msgindex].msg_label
    grouparr[temp_gropindex].RoomsMsg[temp_msgindex].text = newtext;
    gtk_label_set_text (GTK_LABEL(grouparr[temp_gropindex].RoomsMsg[temp_msgindex].msg_label), new_gtext); 
   // }
    gtk_widget_show_all(GTK_WIDGET(chat_stack));
}

void click_on_message(GtkWidget *label, GdkEventButton *event, msg_t* msg) {
    (void)label;
    int tempindex = 0;
    while(grouparr[tempindex].chatroomid != msg->chatroomid && tempindex!= 101){
            tempindex++;
    }
    if (tempindex == 101){
        printf("PIZDAAAAAAAAA\n");
        //return;
    }
    if(grouparr[tempindex].editflag != -1) return;
    if (event->type == GDK_BUTTON_PRESS  &&  event->button == 3 ) {
        GtkWidget *message_poovermenu = gtk_menu_new();
  
        GtkWidget *edit_message_button = gtk_menu_item_new_with_label("Edit");
        add_css_style_by_name(GTK_WIDGET(edit_message_button), "edit_message_button");
        gtk_widget_show(edit_message_button);
        add_css_style_by_name(GTK_WIDGET(edit_message_button), "edit_and_delete_message_button");
        gtk_menu_shell_append(GTK_MENU_SHELL(message_poovermenu), edit_message_button);

        g_signal_connect(G_OBJECT(edit_message_button), "button_press_event", G_CALLBACK(on_edit_message_button_clicked), msg);
        
        GtkWidget *delete_message_button = gtk_menu_item_new_with_label("Delete");
        gtk_widget_show(delete_message_button);
        gtk_menu_shell_append(GTK_MENU_SHELL(message_poovermenu), delete_message_button);
        add_css_style_by_name(GTK_WIDGET(delete_message_button), "edit_and_delete_message_button");
        g_signal_connect(G_OBJECT(delete_message_button), "button_press_event", G_CALLBACK(on_delete_message_button_clicked), &msg->msgid);

        gtk_menu_popup_at_pointer(GTK_MENU(message_poovermenu), NULL);
        add_css_style_by_name(GTK_WIDGET(message_poovermenu), "settings_popovermenu");
        return;
    }
    if (event->type == GDK_BUTTON_PRESS  &&  event->button == 1)
    {
        return;
    }
    
}

