#ifndef PROJECT_SWA_STORAGESYSTEM_H
#define PROJECT_SWA_STORAGESYSTEM_H

#include "../../../../TonicEngine/Headers/Storage/XMLReader.h"
#include "../../../../TonicEngine/Headers/Storage/XMLWriter.h"
#include "../../Storage/Parsers/WorldParser.h"
#include "../../../../TonicEngine/Headers/Storage/StorageFacade.h"

#include "../Components/GravityComponent.h"
#include "../Components/MoveComponent.h"
#include "../Components/TurnComponent.h"

#include <algorithm>


class StorageSystem{//}; : public IBaseSystem {
private:
    XMLReader _reader;
    XMLWriter _writer;
//    StorageFacade _storageFacade;
    std::shared_ptr<EntityManager> _entityManager;
    template <typename Comp> void addComponentTypeOf(std::string compName, std::map<int, MyNode> &components, MyNode &rootNode);
    void saveDrawables();
    void saveGravity();
    void saveMove();
    void savePosition();
    void saveturns();
public:
    StorageSystem();
    ~StorageSystem();

    void assignRelevantEntityManager(std::shared_ptr<EntityManager> entityManager);
    void saveWorld();

    // Pass a string for identifying the world?
    bool loadWorld();
};


#endif //PROJECT_SWA_STORAGESYSTEM_H
