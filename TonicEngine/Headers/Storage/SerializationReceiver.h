#ifndef PROJECT_SWA_SERIALIZATIONRECIEVER_H
#define PROJECT_SWA_SERIALIZATIONRECIEVER_H

#include "DeserializationVisitor.h"
#include "SerializationVisitor.h"

class SerializationReceiver {
public:
    virtual void accept(SerializationVisitor &visitor) = 0;

    virtual void accept(DeserializationVisitor &visitor) {
        accept((SerializationVisitor &) visitor);
    }
};

#endif //PROJECT_SWA_SERIALIZATIONRECIEVER_H
