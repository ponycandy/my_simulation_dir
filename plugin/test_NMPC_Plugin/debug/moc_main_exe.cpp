/****************************************************************************
** Meta object code from reading C++ file 'main_exe.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../main_exe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_exe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_main_exe_t {
    const uint offsetsAndSize[18];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_main_exe_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_main_exe_t qt_meta_stringdata_main_exe = {
    {
QT_MOC_LITERAL(0, 8), // "main_exe"
QT_MOC_LITERAL(9, 9), // "get_state"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 15), // "Eigen::MatrixXd"
QT_MOC_LITERAL(36, 3), // "mat"
QT_MOC_LITERAL(40, 10), // "startsolve"
QT_MOC_LITERAL(51, 12), // "recieve_Byte"
QT_MOC_LITERAL(64, 4), // "data"
QT_MOC_LITERAL(69, 6) // "matget"

    },
    "main_exe\0get_state\0\0Eigen::MatrixXd\0"
    "mat\0startsolve\0recieve_Byte\0data\0"
    "matget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_main_exe[] = {

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
       5,    0,   41,    2, 0x0a,    3 /* Public */,
       6,    1,   42,    2, 0x0a,    4 /* Public */,
       8,    1,   45,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void main_exe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<main_exe *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->get_state((*reinterpret_cast< std::add_pointer_t<Eigen::MatrixXd>>(_a[1]))); break;
        case 1: _t->startsolve(); break;
        case 2: _t->recieve_Byte((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 3: _t->matget((*reinterpret_cast< std::add_pointer_t<Eigen::MatrixXd>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (main_exe::*)(Eigen::MatrixXd );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&main_exe::get_state)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject main_exe::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_main_exe.offsetsAndSize,
    qt_meta_data_main_exe,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_main_exe_t
, QtPrivate::TypeAndForceComplete<main_exe, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Eigen::MatrixXd, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Eigen::MatrixXd, std::false_type>


>,
    nullptr
} };


const QMetaObject *main_exe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *main_exe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_main_exe.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int main_exe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void main_exe::get_state(Eigen::MatrixXd _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
