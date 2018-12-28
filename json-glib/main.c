/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* c语言使用json-glib库构建和解析json格式数据
 * 安装json-glib库
 * 编译：mkdir build && cmake .. && make 或者 gcc main.c `pkg-config --cflags --libs json-glib-1.0`
 */

#include <stdio.h>
#include <json-glib/json-glib.h>
#include <stdio.h>
#include <string.h>

int main()
{
//构建json
	g_type_init();
	JsonObject *obj = json_object_new();
	json_object_set_string_member(obj, "name", "john");
	json_object_set_int_member(obj, "age", 18);
	
	JsonArray *arr = json_array_new();
	json_array_add_string_element(arr, "lily");//{"name":"john","age":18,"friends":["lily","mark"]}
	json_array_add_string_element(arr, "mark");
	json_object_set_array_member(obj, "friends", arr);
	
	JsonGenerator *g = json_generator_new();
	JsonNode *root = json_node_new(JSON_NODE_OBJECT);
	json_node_set_object(root, obj);
	json_generator_set_root(g, root);
	json_generator_to_file(g, "ex.json", NULL);
 
//解析！！！
	JsonParser *parser = json_parser_new();
    JsonNode *node = json_node_new(JSON_NODE_OBJECT);
    json_parser_load_from_file(parser, "ex.json", NULL);
    node = json_parser_get_root(parser);
    JsonObject *obj2 = json_object_new();
    obj2 = json_node_get_object(node);
	const char *aaa = json_object_get_string_member(obj2, "name");
	const int aa = json_object_get_int_member(obj2, "age");
	printf("%s\n", aaa);
	printf("%d\n", aa);
 
	JsonArray *array = json_array_new();
	array = json_object_get_array_member(obj2, "friends");
	const char *bbb = json_array_get_string_element(array, 0);	
	const char *bb = json_array_get_string_element(array, 1);	
	printf("%s\n", bbb);
	printf("%s\n", bb);
	return 0;
}
