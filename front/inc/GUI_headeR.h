#ifndef GHF
#define GHF

#include "../../inc/client.h"

//--------start_window--------

typedef struct msg{
	GtkWidget *msg_box; //BOX in which we put messages
	GtkWidget *msg_label;
	GtkWidget *time_label;
	GtkWidget *name_box;
	GtkWidget *msg_and_name_box;
	GtkWidget *name_label;
	int msgid;
	int senderid;
	int chatroomid; //that's bad code but it somehow works, so
	int hours_sent;
	int minutes_sent;
	char timetext[25];

	int is_edited;

	char sendername[25];
	char *text;
} 			msg_t;

typedef struct chat_s { //for chats
	int editflag;
	GtkWidget *ChatScrolledWondow;
	GtkWidget *ChatBox; //grid where we put those msgs, I should probably do a liked list for those
	GtkWidget *TextField;
	GtkWidget *SendButton;
	GtkWidget *ChatButton;
	int row; //row in whch we put a msg, in the beginnig it's = 0 and then ++ as we add more
	int chatroomid;//selfexplanatory
	char *chatroomname;
	struct msg RoomsMsg[500];
}              chat_t;

extern GtkWidget *start_stack;

extern GtkWidget *start_window, *start_grid, *username_entry,
		         *password_entry, *signin_button, 
		         *registerNow_button, *error_label;
extern GtkWidget *register_grid, *username_reg_entry, *password_reg_entry, 
		  		 *passwordrepeat_reg_entry, *signup_button, *set_up_label,
		  		 *back_button, *error_reg_label, *name_reg_entry, 
		  		 *birthdate_reg_label, *calendar_menubutton;

extern GtkWidget *date_picker, *date_reg_box, *calendar_reg, *pick_calendar_button,
		         *close_calendar_button;

//gui_chat vars
extern GtkWidget *chat_window, *chat_stack, *chatname_buttons_scrolledwindow, 
				*chatname_buttons_box, *welcomepage_button,*messages_scrolledWindow, 
				*messages_viewport, *message_box, *sendMessage_button, *textView_scrolledWindow, 
				*textView_viewport, *message_textView, *find_entry, *actions_menuButton, *chat_grid,
				*settings_popovermenu, *createChat_button, *createGroup_button, *set_groups_users_label, 
       			*set_groups_name_label, *exit_button, *changestile_button, *welcome_page_box, *label_for_astro, 
				*label_for_sign, *label_for_prediciton;

extern int groupcount, editflag, groupcreateflag, stileflag;
extern double from_bottom;
extern char* group_users;
extern chat_t grouparr[100];



extern char *picked_date;
extern bool is_wrong_login, is_wrong_pass;
extern int pass_strength;

extern GError* error;

extern GtkBuilder *builder;
extern GtkCssProvider *provider;
extern GtkStyleContext *context;

//Messaging
void click_on_message(GtkWidget *label, GdkEventButton *event, msg_t* msg);

//Calendar funnctions
void get_and_convert_date_to_string ();
void on_calendar_reg_day_selected_double_click ();
void on_pick_button_clicked ();
void on_close_calendar_date_clicked ();


//CSS functions
void remove_css_style (GtkWidget *widget);
void add_css_style (GtkWidget *widget);
void add_css_style_by_name (GtkWidget *widget, char *name);

//Password entries icon press
void on_password_entry_icon_press();
void on_password_reg_entry_icon_press();
void on_passwordrepeat_reg_entry_icon_press();

//Helper functions
void close_client();
void scroll_down (GtkWidget *scrolled_window);
void change_welcomepage();


//Entries changed
void on_username_entry_changed();
void on_password_entry_changed();
void on_name_reg_entry_changed();
void on_username_reg_entry_changed();
void on_password_reg_entry_changed();
void on_passwordrepeat_reg_entry_changed();

void on_find_entry_changed();
void on_find_entry_activate();

//Entries focus in
gboolean on_username_entry_focus_in_event();
gboolean on_password_entry_focus_in_event();
gboolean on_name_reg_entry_entry_focus_in_event();
gboolean on_username_reg_entry_focus_in_event();
gboolean on_password_reg_entry_focus_in_event();
gboolean on_passwordrepeat_reg_entry_focus_in_event();

gboolean on_messgae_text_view_focus_in_event (GtkWidget *text_view);

//Entries focus out
gboolean on_username_entry_focus_out_event();
gboolean on_password_entry_focus_out_event();
gboolean on_name_reg_entry_entry_focus_out_event();
gboolean on_username_reg_entry_focus_out_event();
gboolean on_password_reg_entry_focus_out_event();
gboolean on_passwordrepeat_reg_entry_focus_out_event();

gboolean on_messgae_text_view_focus_out_event (GtkWidget *text_view);
gboolean on_find_entry_focus_out_event();

//Import from glade
void get_from_glade ();

//Functions for moving through the pages
void on_registerNow_button_clicked();
void on_back_button_clicked();

void on_changestile_button_clicked();
void on_exit_button_clicked();
void on_welcomepage_button_clicked ();
void chatname_button_clicked (GtkWidget *button);
gboolean on_edit_message_button_clicked (GtkWidget *button, GdkEventButton *event, msg_t *msg);
gboolean on_delete_message_button_clicked (GtkWidget *button, GdkEventButton *event, int *message_id);
void send_button_clicked(GtkWidget *button, chat_t *group);
void on_createChat_button_clicked ();
void on_createGroup_button_clicked();
void right_click_on_chat_button(GtkWidget *button, GdkEventButton *event, chat_t* chat);
//----------------------------

#endif
