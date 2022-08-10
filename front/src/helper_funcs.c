#include "../inc/GUI_headeR.h"

void close_client() {
	exit(EXIT_SUCCESS);
}

void wait_answer() {
	while (status_error == -1){
		usleep(10);
	}
}

void scroll_down (GtkWidget *scrolled_window) {
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW(scrolled_window));
    double upper = gtk_adjustment_get_upper ( adjustment );
    gtk_adjustment_set_value (adjustment, upper);
}

void delete_chat_button(int chatroomid){
    int temp_gropindex = 0;
    while(grouparr[temp_gropindex].chatroomid != chatroomid && temp_gropindex!= 101){
        temp_gropindex++;
    }
    if(grouparr[temp_gropindex].chatroomid != chatroomid) return;
	GtkWidget *Dad = gtk_widget_get_ancestor (grouparr[temp_gropindex].ChatButton, GTK_TYPE_EVENT_BOX);
    gtk_container_remove(GTK_CONTAINER(chatname_buttons_box), Dad);
    gtk_widget_show_all(chat_window);
}

void change_welcomepage() {
    add_css_style_by_name(GTK_WIDGET(label_for_astro), "label_for_astro");
    switch (user_info.Zodiack) {
        case ARIES:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_aries");
        break;
    
        case TAURUS:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_taurus");
        break;

        case GEMINI:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_gemini");
        break;

        case CANCER:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_cancer");
        break;

        case LEO:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_leo");
        break;

        case VIRGO:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_virgo");
        break;

        case LIBRA:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_libra");
        break;

        case SCORPIO:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_scorpio");
        break;
        
        case SAGITTARIUS:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_sagittatius");
        break;

        case CAPRICORN:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_capricorn");
        break;

        case AQUARIUS:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_aquarius");
        break;

        case PISCES:
            add_css_style_by_name(GTK_WIDGET(label_for_sign), "label_for_pisces");
        break;
    
        default:
            gtk_label_set_text(GTK_LABEL(label_for_sign), "SIGN_ERROR");
        break;
    }
    gtk_label_set_max_width_chars (GTK_LABEL(label_for_prediciton), 50);
    gtk_label_set_text(GTK_LABEL(label_for_prediciton), user_info.predict);
    add_css_style_by_name(GTK_WIDGET(label_for_prediciton), "label_for_prediction");
}
