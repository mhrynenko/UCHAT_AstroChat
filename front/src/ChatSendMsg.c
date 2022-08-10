#include "../inc/GUI_headeR.h"

void ChatSendMsg(chatmsgdata_t* msg){
    
    int tempindex = 0;
    while(grouparr[tempindex].chatroomid != msg->guid && tempindex!= 101){
        tempindex++;
    }
    if (tempindex == 101){
        printf("PIZDAAAAAAAAA\n");
        return;
    }
    
    int row = grouparr[tempindex].row;
    for (int i = 0; i<=row; i++)
       if(grouparr[tempindex].RoomsMsg[i].msgid == msg->message_id) return;
       

       
    grouparr[tempindex].RoomsMsg[row].msg_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    time_t temp = msg->date;
    struct tm *t = gmtime(&temp); 
    grouparr[tempindex].RoomsMsg[row].hours_sent = t->tm_hour+2;
    grouparr[tempindex].RoomsMsg[row].minutes_sent = t->tm_min;
    if(!msg->is_edited){
        if(t->tm_min < 10) 
            sprintf(grouparr[tempindex].RoomsMsg[row].timetext, "%d:0%d", t->tm_hour+2,t->tm_min);
        else 
            sprintf(grouparr[tempindex].RoomsMsg[row].timetext, "%d:%d", t->tm_hour+2,t->tm_min);
    }
    else {
        if(t->tm_min < 10) 
            sprintf(grouparr[tempindex].RoomsMsg[row].timetext, "%d:0%d(ed.)", t->tm_hour+2,t->tm_min);
        else 
            sprintf(grouparr[tempindex].RoomsMsg[row].timetext, "%d:%d(ed.)", t->tm_hour+2,t->tm_min);
    }

    grouparr[tempindex].RoomsMsg[row].name_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    grouparr[tempindex].RoomsMsg[row].name_label = gtk_label_new(msg->name);
    grouparr[tempindex].RoomsMsg[row].msg_and_name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    grouparr[tempindex].RoomsMsg[row].msg_label = gtk_label_new(msg->text);
    grouparr[tempindex].RoomsMsg[row].msgid = msg->message_id;
    grouparr[tempindex].RoomsMsg[row].is_edited = msg->is_edited;
    grouparr[tempindex].RoomsMsg[row].chatroomid = msg->guid;
    grouparr[tempindex].RoomsMsg[row].time_label = gtk_label_new(grouparr[tempindex].RoomsMsg[row].timetext);
    add_css_style_by_name(GTK_WIDGET(grouparr[tempindex].RoomsMsg[row].time_label), "message_time_label");
    GtkWidget* event_box = gtk_event_box_new();
    gtk_box_pack_start(GTK_BOX(grouparr[tempindex].RoomsMsg[row].msg_and_name_box), grouparr[tempindex].RoomsMsg[row].name_box,FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(grouparr[tempindex].RoomsMsg[row].msg_and_name_box), grouparr[tempindex].RoomsMsg[row].msg_box,FALSE, FALSE, 0);
    //Вставляем имя отправителя
    if (msg->sender_id == user_info.user_id){
        gtk_container_add (GTK_CONTAINER (event_box), grouparr[tempindex].RoomsMsg[row].msg_label);
        gtk_box_pack_end(GTK_BOX(grouparr[tempindex].RoomsMsg[row].msg_box), event_box, FALSE, FALSE, 0);
        gtk_box_set_baseline_position (GTK_BOX(grouparr[tempindex].RoomsMsg[row].msg_box), GTK_BASELINE_POSITION_BOTTOM);
        gtk_box_pack_end(GTK_BOX(grouparr[tempindex].RoomsMsg[row].msg_box), grouparr[tempindex].RoomsMsg[row].time_label,FALSE, FALSE, 0);
        gtk_box_pack_end(GTK_BOX(grouparr[tempindex].RoomsMsg[row].name_box), grouparr[tempindex].RoomsMsg[row].name_label,FALSE, FALSE, 0);
        add_css_style_by_name(GTK_WIDGET(grouparr[tempindex].RoomsMsg[row].msg_label), "message_label_right");
    }
    if (msg->sender_id != user_info.user_id){ 
        gtk_box_pack_start(GTK_BOX(grouparr[tempindex].RoomsMsg[row].msg_box), grouparr[tempindex].RoomsMsg[row].msg_label, FALSE, FALSE, 0);
        gtk_box_set_baseline_position (GTK_BOX(grouparr[tempindex].RoomsMsg[row].msg_box), GTK_BASELINE_POSITION_BOTTOM);
        gtk_box_pack_start(GTK_BOX(grouparr[tempindex].RoomsMsg[row].msg_box), grouparr[tempindex].RoomsMsg[row].time_label,FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(grouparr[tempindex].RoomsMsg[row].name_box), grouparr[tempindex].RoomsMsg[row].name_label,FALSE, FALSE, 0);
        add_css_style_by_name(GTK_WIDGET(grouparr[tempindex].RoomsMsg[row].msg_label), "message_label_left");
    }

    if(msg->sender_id %4 == 1)     add_css_style_by_name(GTK_WIDGET(grouparr[tempindex].RoomsMsg[row].name_label), "username_label_1");
    else if(msg->sender_id%4==2)    add_css_style_by_name(GTK_WIDGET(grouparr[tempindex].RoomsMsg[row].name_label), "username_label_2");
    else if(msg->sender_id%4==3)    add_css_style_by_name(GTK_WIDGET(grouparr[tempindex].RoomsMsg[row].name_label), "username_label_3");
    else    add_css_style_by_name(GTK_WIDGET(grouparr[tempindex].RoomsMsg[row].name_label), "username_label_4");

    gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
    g_signal_connect (G_OBJECT(event_box), "button_press_event", G_CALLBACK(click_on_message), &grouparr[tempindex].RoomsMsg[row]);
    // gtk_widget_realize (event_box);

    gtk_label_set_max_width_chars (GTK_LABEL(grouparr[tempindex].RoomsMsg[row].msg_label), 50);
    gtk_label_set_line_wrap (GTK_LABEL(grouparr[tempindex].RoomsMsg[row].msg_label), TRUE);
    gtk_label_set_line_wrap_mode (GTK_LABEL(grouparr[tempindex].RoomsMsg[row].msg_label), PANGO_WRAP_WORD_CHAR);
    

    //gtk_box_pack_start(GTK_BOX(grouparr[tempindex].ChatBox), grouparr[tempindex].RoomsMsg[row].name_box, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(grouparr[tempindex].ChatBox), grouparr[tempindex].RoomsMsg[row].msg_and_name_box, FALSE, FALSE, 1);
    grouparr[tempindex].row++;
    gtk_widget_show_all(GTK_WIDGET(chat_stack));
    scroll_down(grouparr[tempindex].ChatScrolledWondow);
}

