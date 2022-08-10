#include "../inc/GUI_headeR.h"

void get_from_glade (){
	start_window = GTK_WIDGET(gtk_builder_get_object(builder, "start_window"));
    g_signal_connect(G_OBJECT(start_window), "destroy", G_CALLBACK(close_client), NULL);
	gtk_window_set_title(GTK_WINDOW(start_window), "ASTRO");

	start_stack = GTK_WIDGET(gtk_builder_get_object(builder, "start_stack"));
//------------------------------------------------------------------------------------------------
	start_grid = GTK_WIDGET(gtk_builder_get_object(builder, "start_grid"));

	error_label = GTK_WIDGET(gtk_builder_get_object(builder, "error_label"));

	username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));

	password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));

	signin_button = GTK_WIDGET(gtk_builder_get_object(builder, "signin_button"));

	registerNow_button = GTK_WIDGET(gtk_builder_get_object(builder, "registerNow_button"));
//------------------------------------------------------------------------------------------------	
	register_grid = GTK_WIDGET(gtk_builder_get_object(builder, "register_grid"));

	error_reg_label = GTK_WIDGET(gtk_builder_get_object(builder, "error_reg_label"));

	set_up_label = GTK_WIDGET(gtk_builder_get_object(builder, "set_up_label"));

	name_reg_entry = GTK_WIDGET(gtk_builder_get_object(builder, "name_reg_entry"));

	birthdate_reg_label = GTK_WIDGET(gtk_builder_get_object(builder, "birthdate_reg_label"));
	
	username_reg_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_reg_entry"));

	password_reg_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_reg_entry"));

	passwordrepeat_reg_entry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordrepeat_reg_entry"));

	signup_button = GTK_WIDGET(gtk_builder_get_object(builder, "signup_button"));

	back_button = GTK_WIDGET(gtk_builder_get_object(builder, "back_button"));

	calendar_menubutton = GTK_WIDGET(gtk_builder_get_object(builder, "calendar_menubutton"));
//------------------------------------------------------------------------------------------------
	date_picker = GTK_WIDGET(gtk_builder_get_object(builder, "date_picker"));

	date_reg_box = GTK_WIDGET(gtk_builder_get_object(builder, "date_reg_box"));

	calendar_reg = GTK_WIDGET(gtk_builder_get_object(builder, "calendar_reg"));

	pick_calendar_button = GTK_WIDGET(gtk_builder_get_object(builder, "pick_calendar_button"));

	close_calendar_button = GTK_WIDGET(gtk_builder_get_object(builder, "close_calendar_button"));
//------------------------------------------------------------------------------------------------
}

