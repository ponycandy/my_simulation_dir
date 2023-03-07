/****************************************************************************
** Meta object code from reading C++ file 'simulator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../simulator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Simulator_t {
    QByteArrayData data[8];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Simulator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Simulator_t qt_meta_stringdata_Simulator = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Simulator"
QT_MOC_LITERAL(1, 10, 22), // "sig_agent_state_update"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "QMap<int,Single_agent*>"
QT_MOC_LITERAL(4, 58, 14), // "Agents_group_s"
QT_MOC_LITERAL(5, 73, 20), // "sig_obs_state_update"
QT_MOC_LITERAL(6, 94, 26), // "QMap<int,single_obstacle*>"
QT_MOC_LITERAL(7, 121, 11) // "obs_group_s"

    },
    "Simulator\0sig_agent_state_update\0\0"
    "QMap<int,Single_agent*>\0Agents_group_s\0"
    "sig_obs_state_update\0QMap<int,single_obstacle*>\0"
    "obs_group_s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Simulator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Simulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Simulator *_t = static_cast<Simulator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_agent_state_update((*reinterpret_cast< QMap<int,Single_agent*>(*)>(_a[1]))); break;
        case 1: _t->sig_obs_state_update((*reinterpret_cast< QMap<int,single_obstacle*>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Simulator::*_t)(QMap<int,Single_agent*> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Simulator::sig_agent_state_update)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Simulator::*_t)(QMap<int,single_obstacle*> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Simulator::sig_obs_state_update)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Simulator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Simulator.data,
      qt_meta_data_Simulator,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Simulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Simulator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Simulator.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ODE_functor"))
        return static_cast< ODE_functor*>(this);
    return QObject::qt_metacast(_clname);
}

int Simulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Simulator::sig_agent_state_update(QMap<int,Single_agent*> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Simulator::sig_obs_state_update(QMap<int,single_obstacle*> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
