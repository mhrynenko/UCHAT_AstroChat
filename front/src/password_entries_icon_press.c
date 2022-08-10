#include "../inc/GUI_headeR.h"

void on_password_entry_icon_press() {
	GIcon *icon; 
	GFile *path; 

	if (!gtk_entry_get_visibility(GTK_ENTRY(password_entry))) {
		path = g_file_new_for_path("front/resources/crossed_eye.png"); 
		icon = g_file_icon_new(path); 
		gtk_entry_set_visibility(GTK_ENTRY(password_entry), TRUE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(password_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
	}
	else {
		path = g_file_new_for_path("front/resources/eye.png"); 
		icon = g_file_icon_new(path); 
		gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(password_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
	}
}

void on_password_reg_entry_icon_press() {
	GIcon *icon; 
	GFile *path; 

	if (!gtk_entry_get_visibility(GTK_ENTRY(password_reg_entry))) {
		path = g_file_new_for_path("front/resources/crossed_eye.png"); 
		icon = g_file_icon_new(path); 
		gtk_entry_set_visibility(GTK_ENTRY(password_reg_entry), TRUE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(password_reg_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
		gtk_entry_set_visibility(GTK_ENTRY(passwordrepeat_reg_entry), TRUE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(passwordrepeat_reg_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
	}
	else {
		path = g_file_new_for_path("front/resources/eye.png"); 
		icon = g_file_icon_new(path); 
		gtk_entry_set_visibility(GTK_ENTRY(password_reg_entry), FALSE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(password_reg_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
		gtk_entry_set_visibility(GTK_ENTRY(passwordrepeat_reg_entry), FALSE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(passwordrepeat_reg_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
	}
}

void on_passwordrepeat_reg_entry_icon_press() {
	GIcon *icon; 
	GFile *path; 

	if (!gtk_entry_get_visibility(GTK_ENTRY(passwordrepeat_reg_entry))) {
		path = g_file_new_for_path("front/resources/crossed_eye.png"); 
		icon = g_file_icon_new(path); 
		gtk_entry_set_visibility(GTK_ENTRY(password_reg_entry), TRUE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(password_reg_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
		gtk_entry_set_visibility(GTK_ENTRY(passwordrepeat_reg_entry), TRUE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(passwordrepeat_reg_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
	}
	else {
		path = g_file_new_for_path("front/resources/eye.png"); 
		icon = g_file_icon_new(path); 
		gtk_entry_set_visibility(GTK_ENTRY(password_reg_entry), FALSE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(password_reg_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
		gtk_entry_set_visibility(GTK_ENTRY(passwordrepeat_reg_entry), FALSE);
		gtk_entry_set_icon_from_gicon(GTK_ENTRY(passwordrepeat_reg_entry), GTK_ENTRY_ICON_SECONDARY, icon); 
	}
}
