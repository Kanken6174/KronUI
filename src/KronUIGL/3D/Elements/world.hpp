#include "entity.hpp"
#include "light.hpp"
#include <memory>
#include <vector>

#include <memory>
#include <vector>

class World : public Entity {
protected:
    World& operator=(const World&) = delete;
public:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Light>> lights;

    static std::shared_ptr<World> instance;
    
    static std::shared_ptr<World>& getInstance() {
        if (!instance) {
            instance = std::make_shared<World>();
        }
        return instance;
    }
};

// Initialize the instance outside the class
std::shared_ptr<World> World::instance = nullptr;