#include "../../../inc/client.h"

typedef struct DeleteData
{
	int gid;
	int id;
} deletedata_t;

bool ChatDeleteMsgWrap(void *data)
{
	delete_message(((deletedata_t *)data)->gid, ((deletedata_t *)data)->id);
	//printf("\n===gid %d id %d===\n", ((deletedata_t*)data)->gid, ((deletedata_t*)data)->id);
	return false;
}

char *mx_json_client_get_delete_msg(char *text)
{
	static const char status[] = "0";

	struct json_object *parsed_json = json_tokener_parse(text);
	struct json_object *group;
	struct json_object *message_id;

	json_object_object_get_ex(parsed_json, "group_id", &group);
	json_object_object_get_ex(parsed_json, "id", &message_id);

	int guid = json_object_get_int(group);
	int msg_id = json_object_get_int(message_id);

	deletedata_t *deletedata = malloc(sizeof(deletedata_t));
	deletedata->gid = guid;
	deletedata->id = msg_id;

	gdk_threads_add_idle((GSourceFunc)(&ChatDeleteMsgWrap), (void *)deletedata);
	json_object_put(parsed_json);
	return strdup(status);
}
