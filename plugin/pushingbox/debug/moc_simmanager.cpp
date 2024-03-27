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
    const uint offsetsAndSize[16];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_simmanager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_simmanager_t qt_meta_stringdata_simmanager = {
    {
QT_MOC_LITERAL(0, 10), // "simmanager"
QT_MOC_LITERAL(11, 12), // "state_return"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 15), // "Eigen::MatrixXd"
QT_MOC_LITERAL(41, 3), // "mat"
QT_MOC_LITERAL(45, 11), // "matrecieved"
QT_MOC_LITERAL(57, 13), // "get_state_now"
QT_MOC_LITERAL(71, 12) // "outer_stepin"

    },
    "simmanager\0state_return\0\0Eigen::MatrixXd\0"
    "mat\0matrecieved\0get_state_now\0"
    "outer_stepin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_simmanager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   41,    2, 0x0a,    3 /* Public */,
       6,    0,   44,    2, 0x0a,    5 /* Public */,
       7,    1,   45,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void simmanager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<simmanager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->state_return((*reinterpret_cast< std::add_pointer_t<Eigen::MatrixXd>>(_a[1]))); break;
        case 1: _t->matrecieved((*reinterpret_cast< std::add_pointer_t<Eigen::MatrixXd>>(_a[1]))); break;
        case 2: _t->get_state_now(); break;
        case 3: _t->outer_stepin((*reinterpret_cast< std::add_pointer_t<Eigen::MatrixXd>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (simmanager::*)(Eigen::MatrixXd );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&simmanager::state_return)) {
                *result = 0;
                return;
            }
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
, QtPrivate::TypeAndForceComplete<simmanager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Eigen::MatrixXd, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Eigen::MatrixXd, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Eigen::MatrixXd, std::false_type>


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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void simmanager::state_return(Eigen::MatrixXd _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
