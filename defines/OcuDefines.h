/******************************************************************************
* File:     OcuDefines.h
* Author:   liziqiang
* Company:  xinchuanhui
* Time      2021-07-01
******************************************************************************/
#pragma once

#include <QtGlobal>
#include <QMetaType>
#include <QByteArray>

/**
 *  core中实现的是一个StackWidget
 *  OCU 是整体控制相关的界面
 *  每型车车控是一个StackWidget，车控的界面切换需要在车型的中进行控制
 *  每型车火控是一个StackWidget，火控的界面切换需要在车型的中进行控制
 *  每型车指控是一个StackWidget，火控的界面切换需要在车型的中进行控制
 */

namespace UcsDefines {

//!************************************************************************
//!* ucs view kind                                                        *
//!************************************************************************

typedef enum {
    UCS_VIEW_KIND_NONE = 0,
    UCS_VIEW_KIND_MAIN,                               //! 主界面
    SIM_SIMULATIONCONFIG,
    VEHICLE_WINDOW,                                   //!vehicle 1 interface
    VEHICLE_2_WINDOW,                                   //!vehicle 2 interface

    NETCONFIG_INTERFACE,                                   //!NETCONFIG_INTERFACE 1 interface
    ROSNODEMANAGEMENT,                                   //!ROSNODEMANAGEMENT
    CardataViewer,                                   //!ROSNODEMANAGEMENT
    OCU_VIDEO_WIDGETS,                                   //!ROSNODEMANAGEMENT
    VEHICLE2_CONTROL,                                   //!ROSNODEMANAGEMENT
    VEHICLE2_VIDEO,                                   //!ROSNODEMANAGEMENT
    OCU_MAP_DISPLAY,                                   //!ROSNODEMANAGEMENT
    OCU_ROS_RVIZ,                                   //!ROSNODEMANAGEMENT


    UCS_VIEW_KIND_LOGIN,                               //! 登陆界面
    UCS_VIEW_KIND_USER_MANGER,                         //! user管理界面
    UCS_VIEW_KIND_SYSTEM_SETTING,                      //! 系统设置界面
    UCS_VIEW_KIND_CAR_MANAGER,                         //! 车辆管理界面
    UCS_VIEW_KIND_CAR_NET_PARA_CONFIG,                 //! 车辆网络参数配置界面
    UCS_VIEW_KIND_RADIO_MANAGER,                       //! 电台管理界面

    UCS_VIEW_KIND_ACCOUNT_MANAGEMENT,                  //! 账户管理界面
    UCS_VIEW_KIND_PLUS_ACCOUNT_MANAGEMENT,             //! 三级用户管理界面
    UCS_VIEW_KIND_LOG_MANAGER,                         //!
    UCS_VIEW_KIND_OUTPUR_INFO,                         //!
    UCS_VIEW_KIND_COMMAND_INFO,                        //!
    UCS_VIEW_KIND_MAP,                                 //! 地图界面
    UCS_VIEW_KIND_ENABLE,

    UCS_VIEW_KIND_SUB_CORE,                            //! 第二张界面主界面
    UCS_VIEW_KIND_SUB_CORE_MAP,                        //! 第二张界面地图界面
    UCS_VIEW_KIND_SUB_CORE_VIDEO,                      //! 第二张界面视频界面


    UCS_VIEW_KIND_MIANWIDOW_CORE,                      //!整体框架的主界面                                 //ROSNODEMANAGEMENT
} UcsViewKind;

typedef enum {
    UCS_VIEW_INDEX_NONE = 0,
    UCS_VIEW_INDEX_QXXLC,
    UCS_VIEW_INDEX_ZXLSC,
    UCS_VIEW_INDEX_ZXLDC,
    UCS_VIEW_INDEX_XXDZZ,
    UCS_VIEW_INDEX_ZXBLG,
    UCS_VIEW_INDEX_XXFKC,
    UCS_VIEW_INDEX_207LSC,
    UCS_VIEW_INDEX_QXXLC_FIRECONTROL,
    UCS_VIEW_INDEX_ZXLSC_FIRECONTROL,
    UCS_VIEW_INDEX_ZXLDC_FIRECONTROL,
    UCS_VIEW_INDEX_XXDZZ_FIRECONTROL,
    UCS_VIEW_INDEX_ZXBLG_FIRECONTROL,
    UCS_VIEW_INDEX_XXFKC_FIRECONTROL,
    UCS_VIEW_INDEX_207LSC_FIRECONTROL
}UcsViewIndex;

//!** **********************************************************************
//!* ucs data kind                                                         *
//!*************************************************************************
}

