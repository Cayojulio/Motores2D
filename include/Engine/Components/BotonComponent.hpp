#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"

class BotonComponent : public Component
{
private:
    bool m_encima{false};

public:
    void Update(float dt) override;

    bool EstaEncima() const { return m_encima; }
};
