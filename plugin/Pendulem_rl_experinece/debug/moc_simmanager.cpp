/****************************************************************************
** Meta object code from reading C++ file 'simmanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../simmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_simmanager_t {
    const uint offsetsAndSize[12];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_simmanager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_simmanager_t qt_meta_stringdata_simmanager = {
    {
QT_MOC_LITERAL(0, 10), // "simmanager"
QT_MOC_LITERAL(11, 11), // "matrecieved"
QT_MOC_LITERAL(23, 0), // ""
QT_MOC_LITERAL(24, 15), // "Eigen::MatrixXd"
QT_MOC_LITERAL(40, 3), // "mat"
QT_MOC_LITERAL(44, 12) // "requeststate"

    },
    "simmanager\0matrecieved\0\0Eigen::MatrixXd\0"
    "mat\0requeststate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_simmanager[] = {

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
       1,    1,   26,    2, 0x0a,    1 /* Public */,
       5,    1,   29,    2, 0x0a,    3 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void simmanager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<simmanager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->matrecieved((*reinterpret_cast< std::add_pointer_t<Eigen::MatrixXd>>(_a[1]))); break;
        case 1: _t->requeststate((*reinterpret_cast< std::add_pointer_t<Eigen::MatrixXd>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject simmanager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_simmanager.offsetsAndSize,
    qt_meta_data_simmanager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_simmanager_t
, QtPrivate::TypeAndForceComplete<simmanager, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Eigen::MatrixXd, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Eigen::MatrixXd, std::false_type>


>,
    nullptr
} };


const QMetaObject *simmanager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *simmanager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_simmanager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int simmanager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
