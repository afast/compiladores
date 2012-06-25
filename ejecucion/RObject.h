#ifndef _ROBJECT_H
#define _ROBJECT_H

enum obj_type { RBOOL, RSTRING, ROBJECT, RINT, RCLASS, RARRAY, RNIL, RNUMERIC};

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
    virtual RString *get_class();
    virtual bool respond_to(RString *method);
    virtual RString* to_s();
    virtual bool operator== (RObject param);
};
#endif
