#ifndef _ROBJECT_H
#define _ROBJECT_H

enum obj_type { RBOOL, RSTRING, ROBJECT, RINT, RCLASS, RARRAY, RNIL, RNUMERIC, RVARIABLE, RCOMMAND };

class RInteger;
class RString;
class RBool;

class RObject {
  protected:
    long int object_id;
  public:
    enum obj_type type;
    RObject();
    RInteger *objectId();
    bool is_numeric();
    bool is_string();
    bool is_command();
    bool is_int();
    bool is_decimal();
    bool is_array();
    bool is_nil();
    virtual RString *get_class();
    virtual bool respond_to(RString *method);
    virtual RString* to_s();
};
#endif
