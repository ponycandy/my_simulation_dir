/****************************************************************************
** Meta object code from reading C++ file 'mypainter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mypainter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mypainter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MYpainter_t {
    QByteArrayData data[8];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MYpainter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MYpainter_t qt_meta_stringdata_MYpainter = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MYpainter"
QT_MOC_LITERAL(1, 10, 17), // "slot_update_state"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 23), // "QMap<int,Single_agent*>"
QT_MOC_LITERAL(4, 53, 10), // "agentgroup"
QT_MOC_LITERAL(5, 64, 21), // "slot_obs_state_update"
QT_MOC_LITERAL(6, 86, 26), // "QMap<int,single_obstacle*>"
QT_MOC_LITERAL(7, 113, 9) // "obs_group"

    },
    "MYpainter\0slot_update_state\0\0"
    "QMap<int,Single_agent*>\0agentgroup\0"
    "slot_obs_state_update\0QMap<int,single_obstacle*>\0"
    "obs_group"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MYpainter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       5,    1,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void MYpainter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MYpainter *_t = static_cast<MYpainter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_update_state((*reinterpret_cast< QMap<int,Single_agent*>(*)>(_a[1]))); break;
        case 1: _t->slot_obs_state_update((*reinterpret_cast< QMap<int,single_obstacle*>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MYpainter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MYpainter.data,
      qt_meta_data_MYpainter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MYpainter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MYpainter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MYpainter.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "DrawOperation"))
        return static_cast< DrawOperation*>(this);
    return QObject::qt_metacast(_clname);
}

int MYpainter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
