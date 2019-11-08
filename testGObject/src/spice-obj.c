
#include "spice-obj.h"

#include "header.h"


enum{
    SPICE_OBJ_SIG1,
    SPICE_OBJ_SIG2,
    SPICE_OBJ_SIG3,
    SPICE_OBJ_SIG4,
    SPICE_OBJ_LAST_SIGNAL,
};

static guint signals[SPICE_OBJ_LAST_SIGNAL];


/* VOID:INT,INT,POINTER  */
static void g_cclosure_user_marshal_VOID__INT_INT_POINTER (GClosure     *closure,
                                                            GValue       *return_value,
                                                            guint         n_param_values,
                                                            const GValue *param_values,
                                                            gpointer      invocation_hint,
                                                            gpointer      marshal_data){

    LOGD("g_cclosure_user_marshal_VOID__INT_INT_POINTER");
    typedef void (*GMarshalFunc_VOID__INT_INT_POINTER) (gpointer data1,
                                                                gint arg1,
                                                                gint arg2,
                                                                gpointer arg3,
                                                                gpointer data2);
    GCClosure *cc = (GCClosure *) closure;
    gpointer data1, data2;
    GMarshalFunc_VOID__INT_INT_POINTER callback;

    g_return_if_fail (n_param_values == 4);

    if (G_CCLOSURE_SWAP_DATA (closure))
      {
        data1 = closure->data;
        data2 = g_value_peek_pointer (param_values + 0);
      }
    else
      {
        data1 = g_value_peek_pointer (param_values + 0);
        data2 = closure->data;
      }
    callback = (GMarshalFunc_VOID__INT_INT_POINTER) (marshal_data ? marshal_data : cc->callback);

    callback (data1,
              g_value_get_int (param_values + 1),
              g_value_get_int (param_values + 2),
              g_value_get_pointer (param_values + 3),
              data2);
}


struct _SpiceObjPrivate{
    int i;
};


G_DEFINE_TYPE_WITH_PRIVATE (SpiceObj,spice_obj, G_TYPE_OBJECT)

static void spice_obj_set_property(GObject *object,guint property_id,const GValue *value,GParamSpec *pspec){
    LOGD("spice_obj_set_property");
}

static void spice_obj_get_property(GObject *object,guint  property_id,GValue *value,GParamSpec *pspec){
    LOGD("spice_obj_get_property");
}

static void spice_obj_dispose	(GObject *object){
    LOGD("spice_obj_dispose");
}

static void spice_obj_finalize(GObject *object){
    LOGD("spice_obj_finalize");
}

static void spice_obj_constructed(GObject *object){
     LOGD("spice_obj_constructed");


}


static void spice_obj_init(SpiceObj* self){
    LOGD("spice_obj_init");
    self->priv = spice_obj_get_instance_private(self);
}



static void spice_obj_class_init(SpiceObjClass* klass){
    LOGD("spice_obj_class_init\n");

    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

    gobject_class->constructed = spice_obj_constructed;
    gobject_class->get_property = spice_obj_get_property;
    gobject_class->set_property = spice_obj_set_property;
    gobject_class->finalize = spice_obj_finalize;
    gobject_class->dispose = spice_obj_dispose;


    signals[SPICE_OBJ_SIG1] =
            g_signal_new("spice-created",
                         G_OBJECT_CLASS_TYPE(klass),
                         G_SIGNAL_RUN_FIRST|G_SIGNAL_DETAILED,
                         G_STRUCT_OFFSET(SpiceObjClass, spice_created),
                         NULL, NULL,
                         g_cclosure_user_marshal_VOID__INT_INT_POINTER,
                         G_TYPE_NONE,
                         3,
                         G_TYPE_INT, G_TYPE_INT,
                         G_TYPE_POINTER);
}


void emit_spice_created(SpiceObj* obj){
    LOGD("emit_spice_created");
     g_signal_emit(obj, signals[SPICE_OBJ_SIG1],0,1920,1080,obj);
}
