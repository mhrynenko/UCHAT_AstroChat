#include "../inc/GUI_headeR.h"

GtkWidget *chat_window;

GtkWidget *chat_stack;

GtkWidget *chatname_buttons_scrolledwindow, *chatname_buttons_box, *welcomepage_button;

GtkWidget *messages_scrolledWindow, *messages_viewport, *message_box;

GtkWidget *sendMessage_button, *textView_scrolledWindow, *textView_viewport, 
          *message_textView; 

GtkWidget *find_entry, *actions_menuButton, *chat_grid;

GtkWidget *settings_popovermenu, *createChat_button, *createGroup_button, *set_groups_users_label, 
        *set_groups_name_label, *exit_button, *changestile_button;

GtkWidget *welcome_page_box, *label_for_astro, *label_for_sign, *label_for_prediciton;


int groupcount, editflag, groupcreateflag = 0, stileflag = 1;
double from_bottom = 0.0;
char* group_users;
chat_t grouparr[100];

void GUI_chat() {
    builder = gtk_builder_new();

	if (!gtk_builder_add_from_file (builder, "front/resources/chat_window.glade", &error)) {
		/* загрузить файл не удалось */
		g_critical("Can't open file: %s", error->message);
		g_error_free(error);
	}
    //stileflag = 0;
	gtk_builder_connect_signals(builder, NULL);

    provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "front/resources/theme_chat.css", NULL);

    chat_window = GTK_WIDGET(gtk_builder_get_object(builder, "chat_window"));
    g_signal_connect(G_OBJECT(chat_window), "destroy", G_CALLBACK(close_client), NULL);
	gtk_window_set_title(GTK_WINDOW(chat_window), "ASTRO");

    chat_stack = GTK_WIDGET(gtk_builder_get_object(builder, "chat_stack"));
    chatname_buttons_scrolledwindow = GTK_WIDGET(gtk_builder_get_object(builder, "chatname_buttons_scrolledwindow"));
    add_css_style_by_name(GTK_WIDGET(chatname_buttons_scrolledwindow), "chatname_scrolledwindow");

    chatname_buttons_box = GTK_WIDGET(gtk_builder_get_object(builder, "chatname_buttons_box"));

    welcomepage_button = GTK_WIDGET(gtk_builder_get_object(builder, "welcomepage_button"));
    add_css_style(welcomepage_button);

    messages_scrolledWindow = GTK_WIDGET(gtk_builder_get_object(builder, "messages_scrolledWindow"));
    messages_viewport = GTK_WIDGET(gtk_builder_get_object(builder, "messages_viewport"));
    chat_grid = GTK_WIDGET(gtk_builder_get_object(builder, "chat_grid"));
    message_box = GTK_WIDGET(gtk_builder_get_object(builder, "message_box"));
    sendMessage_button = GTK_WIDGET(gtk_builder_get_object(builder, "sendMessage_button"));
    textView_scrolledWindow = GTK_WIDGET(gtk_builder_get_object(builder, "textView_scrolledWindow"));
    textView_viewport = GTK_WIDGET(gtk_builder_get_object(builder, "textView_viewport"));
    message_textView = GTK_WIDGET(gtk_builder_get_object(builder, "message_textView"));
    find_entry = GTK_WIDGET(gtk_builder_get_object(builder, "find_entry"));
    add_css_style_by_name(GTK_WIDGET(find_entry), "find_entry");

    actions_menuButton = GTK_WIDGET(gtk_builder_get_object(builder, "actions_menuButton"));
    add_css_style_by_name(GTK_WIDGET(actions_menuButton), "more_menubutton");
    settings_popovermenu = GTK_WIDGET(gtk_builder_get_object(builder, "settings_popovermenu"));
    // gtk_widget_set_events (GTK_WIDGET(settings_popovermenu), GDK_FOCUS_CHANGE_MASK);
    // g_signal_connect (G_OBJECT (settings_popovermenu), "focus-out-event", G_CALLBACK (on_settings_popovermenu_focus_out), NULL);
    add_css_style_by_name(GTK_WIDGET(settings_popovermenu), "settings_popovermenu");

    createChat_button = GTK_WIDGET(gtk_builder_get_object(builder, "createChat_button"));
    add_css_style_by_name(GTK_WIDGET(createChat_button), "create_chat_button");

    changestile_button = GTK_WIDGET(gtk_builder_get_object(builder, "changestile_button"));
    add_css_style_by_name(GTK_WIDGET(changestile_button), "create_chat_button");

    createGroup_button = GTK_WIDGET(gtk_builder_get_object(builder, "createGroup_button"));
    add_css_style_by_name(GTK_WIDGET(createGroup_button), "create_chat_button");
    set_groups_users_label = gtk_label_new("Set group's users");
    set_groups_name_label = gtk_label_new("Set group's name");
    gtk_button_set_label(GTK_BUTTON(createGroup_button), "   Group's users");

    exit_button = GTK_WIDGET(gtk_builder_get_object(builder, "exit_button"));
    add_css_style_by_name(GTK_WIDGET(exit_button), "exit_button");

    welcome_page_box = GTK_WIDGET(gtk_builder_get_object(builder, "welcome_page_box"));

    label_for_astro = GTK_WIDGET(gtk_builder_get_object(builder, "label_for_astro"));

    label_for_sign = GTK_WIDGET(gtk_builder_get_object(builder, "label_for_sign"));

    label_for_prediciton = GTK_WIDGET(gtk_builder_get_object(builder, "label_for_prediciton"));
    gtk_label_set_justify (GTK_LABEL(label_for_prediciton), GTK_JUSTIFY_CENTER);
    gtk_label_set_line_wrap (GTK_LABEL(label_for_prediciton), TRUE);
    gtk_label_set_line_wrap_mode (GTK_LABEL(label_for_prediciton), PANGO_WRAP_WORD_CHAR);

    change_welcomepage();

    add_css_style_by_name(GTK_WIDGET(chat_window), "chat_window");
    gtk_window_set_title (GTK_WINDOW(chat_window), "Welcome to the AstroChat");
	// gtk_window_set_position(GTK_WINDOW(ChatWindow), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(chat_window);

    // gtk_main();
}
