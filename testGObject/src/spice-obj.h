
#ifndef __SPICE_OBJ_H__
#define __SPICE_OBJ_H__




#include <glib-object.h>
G_BEGIN_DECLS

#define SPICE_TYPE_OBJ                  (spice_obj_get_type ())
#define SPICE_OBJ(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), SPICE_TYPE_OBJ, SpiceObj))
#define SPICE_IS_OBJ(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SPICE_TYPE_OBJ))
#define SPICE_OBJ_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), SPICE_TYPE_OBJ, SpiceObjClass))
#define SPICE_IS_OBJ_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), SPICE_TYPE_OBJ))
#define SPICE_OBJ_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), SPICE_TYPE_OBJ, SpiceObjClass))


typedef struct _SpiceObj SpiceObj;
typedef struct _SpiceObjClass SpiceObjClass;
typedef struct _SpiceObjPrivate SpiceObjPrivate;

struct _SpiceObj{
	GObject parent;
    SpiceObjPrivate* priv;
};

struct _SpiceObjClass{
	GObjectClass parent_class;

    /* signals */
    void (*spice_created)(SpiceObj* obj,int widht,int height,gpointer data);
};




GType spice_obj_get_type(void);


void emit_spice_created(SpiceObj* obj);


G_END_DECLS

#endif
