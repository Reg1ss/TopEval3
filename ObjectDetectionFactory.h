//
// Created by zhoub on 18-5-16.
//

#ifndef TPDLENGINE_TPOBJECTDETECTIONFACTORY_H
#define TPDLENGINE_TPOBJECTDETECTIONFACTORY_H
#include "ObjectDetection.h"

namespace tpv
{
    class ObjectDetectionFactory
    {
    public:
        virtual ~ObjectDetectionFactory(){};
        std::shared_ptr<ObjectDetection> Create(const ObjectDetectionInitParams &objectDetectionInitParams);
    };
}

#endif //TPDLENGINE_TPOBJECTDETECTIONFACTORY_H
