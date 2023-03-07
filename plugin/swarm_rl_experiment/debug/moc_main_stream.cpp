/****************************************************************************
** Meta object code from reading C++ file 'main_stream.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../main_stream.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_stream.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_main_stream_t {
    QByteArrayData data[6];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_main_stream_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_main_stream_t qt_meta_stringdata_main_stream = {
    {
QT_MOC_LITERAL(0, 0, 11), // "main_stream"
QT_MOC_LITERAL(1, 12, 9), // "step_once"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "matrecieved"
QT_MOC_LITERAL(4, 35, 15), // "Eigen::MatrixXd"
QT_MOC_LITERAL(5, 51, 3) // "mat"

    },
    "main_stream\0step_once\0\0matrecieved\0"
    "Eigen::MatrixXd\0mat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_main_stream[] = {

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
       1,    0,   24,    2, 0x0a /* Public */,
       3,    1,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void main_stream::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        main_stream *_t = static_cast<main_stream *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->step_once(); break;
        case 1: _t->matrecieved((*reinterpret_cast< Eigen::MatrixXd(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject main_stream::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_main_stream.data,
      qt_meta_data_main_stream,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *main_stream::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *main_stream::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_main_stream.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int main_stream::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
