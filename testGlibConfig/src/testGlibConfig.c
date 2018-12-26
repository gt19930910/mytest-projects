#include "testGlibConfig.h"

gboolean TestGlibConfig(char *pFilePath)
{
    gchar *conf_file, *conf;
    GKeyFile *keyfile = NULL;
    GError *error = NULL;
    gchar **keys = NULL;
    gsize nkeys, i;

    /*创建对象*/
    keyfile = g_key_file_new();

    /*打开配置文件*/
    conf_file = g_build_filename(pFilePath, NULL);
    if (!g_key_file_load_from_file(keyfile, conf_file,
                                   G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS, &error)) {
        g_clear_error(&error);
    	return FALSE;
    }

    /*读取配置文件的general类别有几个小字段*/
    keys = g_key_file_get_keys(keyfile, "general", &nkeys, &error);
    g_print("%d\n", nkeys);

    for (i = 0; i < nkeys; ++i) {
        g_print("%s\n", keys[i]);
    }

    /*获取gt类别下的abc字段的string*/
    gchar *str = g_key_file_get_string(keyfile, "gt", "abc", &error);
    g_print("%s\n", str);
    g_free(str);

    /*获取ui类别下的toolbar字段的bool*/
    gboolean state = g_key_file_get_boolean(keyfile, "ui", "toolbar", &error);
    if (state)
        g_print("true\n");

    g_key_file_set_boolean(keyfile, "gt", "def", 0);
    g_key_file_set_string(keyfile, "gt", "abc", "hi");

    if ((conf = g_key_file_to_data(keyfile, NULL, &error)) == NULL ||
        !g_file_set_contents(conf_file, conf, -1, &error)) {
        g_error_free(error);
        error = NULL;
    }

    /*销毁*/
    g_free(conf);
    g_free(conf_file);
    g_key_file_free(keyfile);

    return TRUE;
}