#include "domain/ListenerFactory.hpp"

using namespace backing::domain;

ListenerFactory::ListenerFactory(std::shared_ptr<Logger> logger):
        logger(std::move(logger))
{

}

std::shared_ptr<Listener> ListenerFactory::getListener()
{
    return std::make_shared<CppRestRequestListener>();
}
