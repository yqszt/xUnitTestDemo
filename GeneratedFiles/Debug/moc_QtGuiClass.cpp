/****************************************************************************
** Meta object code from reading C++ file 'QtGuiClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../view/QtGuiClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtGuiClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtGuiClass_t {
    QByteArrayData data[18];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtGuiClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtGuiClass_t qt_meta_stringdata_QtGuiClass = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QtGuiClass"
QT_MOC_LITERAL(1, 11, 12), // "resizeWindow"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 1), // "w"
QT_MOC_LITERAL(4, 27, 1), // "h"
QT_MOC_LITERAL(5, 29, 11), // "changeState"
QT_MOC_LITERAL(6, 41, 8), // "function"
QT_MOC_LITERAL(7, 50, 5), // "shape"
QT_MOC_LITERAL(8, 56, 4), // "path"
QT_MOC_LITERAL(9, 61, 11), // "setPenColor"
QT_MOC_LITERAL(10, 73, 5), // "color"
QT_MOC_LITERAL(11, 79, 10), // "setPenSize"
QT_MOC_LITERAL(12, 90, 5), // "width"
QT_MOC_LITERAL(13, 96, 11), // "setProperty"
QT_MOC_LITERAL(14, 108, 9), // "_PROPERTY"
QT_MOC_LITERAL(15, 118, 1), // "p"
QT_MOC_LITERAL(16, 120, 14), // "setTemperature"
QT_MOC_LITERAL(17, 135, 1) // "T"

    },
    "QtGuiClass\0resizeWindow\0\0w\0h\0changeState\0"
    "function\0shape\0path\0setPenColor\0color\0"
    "setPenSize\0width\0setProperty\0_PROPERTY\0"
    "p\0setTemperature\0T"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtGuiClass[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,   49,    2, 0x0a /* Public */,
       9,    1,   56,    2, 0x0a /* Public */,
      11,    1,   59,    2, 0x0a /* Public */,
      13,    1,   62,    2, 0x0a /* Public */,
      16,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,    6,    7,    8,
    QMetaType::Void, QMetaType::QColor,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::Double,   17,

       0        // eod
};

void QtGuiClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtGuiClass *_t = static_cast<QtGuiClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resizeWindow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->changeState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->setPenColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 3: _t->setPenSize((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->setProperty((*reinterpret_cast< _PROPERTY(*)>(_a[1]))); break;
        case 5: _t->setTemperature((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QtGuiClass::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtGuiClass::resizeWindow)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QtGuiClass::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QtGuiClass.data,
      qt_meta_data_QtGuiClass,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QtGuiClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtGuiClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtGuiClass.stringdata0))
        return static_cast<void*>(const_cast< QtGuiClass*>(this));
    return QWidget::qt_metacast(_clname);
}

int QtGuiClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QtGuiClass::resizeWindow(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
