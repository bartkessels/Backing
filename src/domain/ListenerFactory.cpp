#include "domain/ListenerFactory.hpp"

using namespace backing::domain;

std::shared_ptr<Listener> ListenerFactory::getListener()
{
    return std::make_shared<CppRestRequestListener>();
}
