/****************************************************************************
** Meta object code from reading C++ file 'NMPC_TrajPlanningActivator.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../NMPC_TrajPlanningActivator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NMPC_TrajPlanningActivator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NMPC_TrajPlanningActivator_t {
    const uint offsetsAndSize[2];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_NMPC_TrajPlanningActivator_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_NMPC_TrajPlanningActivator_t qt_meta_stringdata_NMPC_TrajPlanningActivator = {
    {
QT_MOC_LITERAL(0, 26) // "NMPC_TrajPlanningActivator"

    },
    "NMPC_TrajPlanningActivator"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NMPC_TrajPlanningActivator[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void NMPC_TrajPlanningActivator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject NMPC_TrajPlanningActivator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NMPC_TrajPlanningActivator.offsetsAndSize,
    qt_meta_data_NMPC_TrajPlanningActivator,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_NMPC_TrajPlanningActivator_t
, QtPrivate::TypeAndForceComplete<NMPC_TrajPlanningActivator, std::true_type>



>,
    nullptr
} };


const QMetaObject *NMPC_TrajPlanningActivator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NMPC_TrajPlanningActivator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NMPC_TrajPlanningActivator.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PluginInterface"))
        return static_cast< PluginInterface*>(this);
    if (!strcmp(_clname, "Examples.Plugin.PluginInterface_iid"))
        return static_cast< PluginInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int NMPC_TrajPlanningActivator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData_NMPC_TrajPlanningActivator[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x23,  'E',  'x',  'a',  'm',  'p', 
    'l',  'e',  's',  '.',  'P',  'l',  'u',  'g', 
    'i',  'n',  '.',  'P',  'l',  'u',  'g',  'i', 
    'n',  'I',  'n',  't',  'e',  'r',  'f',  'a', 
    'c',  'e',  '_',  'i',  'i',  'd', 
    // "className"
    0x03,  0x78,  0x1a,  'N',  'M',  'P',  'C',  '_', 
    'T',  'r',  'a',  'j',  'P',  'l',  'a',  'n', 
    'n',  'i',  'n',  'g',  'A',  'c',  't',  'i', 
    'v',  'a',  't',  'o',  'r', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(NMPC_TrajPlanningActivator, NMPC_TrajPlanningActivator)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
