/****************************************************************************
** Meta object code from reading C++ file 'mypainter.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mypainter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mypainter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MYpainter_t {
    const uint offsetsAndSize[16];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MYpainter_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MYpainter_t qt_meta_stringdata_MYpainter = {
    {
QT_MOC_LITERAL(0, 9), // "MYpainter"
QT_MOC_LITERAL(10, 17), // "slot_update_state"
QT_MOC_LITERAL(28, 0), // ""
QT_MOC_LITERAL(29, 13), // "QList<double>"
QT_MOC_LITERAL(43, 11), // "state_array"
QT_MOC_LITERAL(55, 8), // "setstate"
QT_MOC_LITERAL(64, 15), // "Eigen::MatrixXd"
QT_MOC_LITERAL(80, 5) // "state"

    },
    "MYpainter\0slot_update_state\0\0QList<double>\0"
    "state_array\0setstate\0Eigen::MatrixXd\0"
    "state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MYpainter[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x08,    1 /* Private */,
       5,    1,   29,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void MYpainter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MYpainter *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_update_state((*reinterpret_cast< std::add_pointer_t<QList<double>>>(_a[1]))); break;
        case 1: _t->setstate((*reinterpret_cast< std::add_pointer_t<Eigen::MatrixXd>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<double> >(); break;
            }
            break;
        }
    }
}

const QMetaObject MYpainter::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MYpainter.offsetsAndSize,
    qt_meta_data_MYpainter,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MYpainter_t
, QtPrivate::TypeAndForceComplete<MYpainter, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QVector<double>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Eigen::MatrixXd, std::false_type>


>,
    nullptr
} };


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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
