#include "domain/RequestListenerFactory.hpp"

using namespace backing::domain;

RequestListenerFactory::RequestListenerFactory(std::shared_ptr<Logger> logger):
    logger(std::move(logger))
{

}

std::shared_ptr<RequestListener> RequestListenerFactory::getRequestListener()
{
    return std::make_shared<CppRestRequestListener>(logger);
}