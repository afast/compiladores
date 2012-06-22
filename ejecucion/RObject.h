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
    virtual bool respond_to(RString *method);
    virtual bool operator== (RObject param);
    virtual RObject operator+ (RObject op);
};
#endif
