#include "cameramanager.h"

CameraManager::CameraManager()
{
    controller=new Cameracontroller;
    controller->show();
}
