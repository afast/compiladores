#ifndef _ROBJECT_H
#define _ROBJECT_H

class RInteger;
class RString;
class RBool;

class RObject {
  protected:
    long int object_id;
  public:
    RObject();
    RInteger *objectId();
    virtual RString *get_class();
    virtual RBool *respond_to(RString *method);
};
#endif
