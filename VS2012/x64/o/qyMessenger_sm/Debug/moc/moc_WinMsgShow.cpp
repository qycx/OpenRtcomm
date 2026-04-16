/****************************************************************************
** Meta object code from reading C++ file 'WinMsgShow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../openRtComm-windows-sm/srcProjs/srcRoot/src6/qyMessenger_sm/qyMessenger_sm/WinMsgShow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WinMsgShow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN17WinQWebEnginePageE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN17WinQWebEnginePageE = QtMocHelpers::stringData(
    "WinQWebEnginePage"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN17WinQWebEnginePageE[] = {

 // content:
      12,       // revision
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

Q_CONSTINIT const QMetaObject WinQWebEnginePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWebEnginePage::staticMetaObject>(),
    qt_meta_stringdata_ZN17WinQWebEnginePageE.offsetsAndSizes,
    qt_meta_data_ZN17WinQWebEnginePageE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN17WinQWebEnginePageE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WinQWebEnginePage, std::true_type>
    >,
    nullptr
} };

void WinQWebEnginePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WinQWebEnginePage *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *WinQWebEnginePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WinQWebEnginePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN17WinQWebEnginePageE.stringdata0))
        return static_cast<void*>(this);
    return QWebEnginePage::qt_metacast(_clname);
}

int WinQWebEnginePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebEnginePage::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN10MsgHtmlObjE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MsgHtmlObjE = QtMocHelpers::stringData(
    "MsgHtmlObj",
    "signalMsgHtml",
    "",
    "html",
    "FileMessageProgress",
    "mesid",
    "progress",
    "iStatus",
    "userid",
    "isObjType",
    "fileRecv",
    "msgid",
    "fileCancel",
    "openFile",
    "fileName",
    "showMore",
    "page",
    "clickReceive",
    "msg",
    "clickHeader",
    "chatType",
    "clickLeftHeader",
    "msgLHtmlTmpl",
    "msgRHtmlTmpl",
    "msgRHtmlFile",
    "msgLHtmlFile"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MsgHtmlObjE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       4,  111, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    5 /* Public */,
       4,    5,   71,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,   82,    2, 0x0a,   13 /* Public */,
      12,    1,   85,    2, 0x0a,   15 /* Public */,
      13,    3,   88,    2, 0x0a,   17 /* Public */,
      15,    1,   95,    2, 0x0a,   21 /* Public */,
      17,    2,   98,    2, 0x0a,   23 /* Public */,
      19,    2,  103,    2, 0x0a,   26 /* Public */,
      21,    1,  108,    2, 0x0a,   29 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int,    5,    6,    7,    8,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   11,    8,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,   20,
    QMetaType::Void, QMetaType::Int,    8,

 // properties: name, type, flags, notifyId, revision
      22, QMetaType::QString, 0x00015003, uint(0), 0,
      23, QMetaType::QString, 0x00015003, uint(0), 0,
      24, QMetaType::QString, 0x00015003, uint(0), 0,
      25, QMetaType::QString, 0x00015003, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject MsgHtmlObj::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN10MsgHtmlObjE.offsetsAndSizes,
    qt_meta_data_ZN10MsgHtmlObjE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MsgHtmlObjE_t,
        // property 'msgLHtmlTmpl'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'msgRHtmlTmpl'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'msgRHtmlFile'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'msgLHtmlFile'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MsgHtmlObj, std::true_type>,
        // method 'signalMsgHtml'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'FileMessageProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'fileRecv'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'fileCancel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'openFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'showMore'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'clickReceive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'clickHeader'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'clickLeftHeader'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MsgHtmlObj::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MsgHtmlObj *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signalMsgHtml((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->FileMessageProgress((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 2: _t->fileRecv((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->fileCancel((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->openFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 5: _t->showMore((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->clickReceive((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->clickHeader((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 8: _t->clickLeftHeader((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (MsgHtmlObj::*)(const QString & );
            if (_q_method_type _q_method = &MsgHtmlObj::signalMsgHtml; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (MsgHtmlObj::*)(const QString & , QString , int , QString , int );
            if (_q_method_type _q_method = &MsgHtmlObj::FileMessageProgress; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->m_msgLHtmlTmpl; break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->m_msgRHtmlTmpl; break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->m_msgRHtmlFile; break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->m_msgLHtmlFile; break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_msgLHtmlTmpl != *reinterpret_cast< QString*>(_v)) {
                _t->m_msgLHtmlTmpl = *reinterpret_cast< QString*>(_v);
                Q_EMIT _t->signalMsgHtml(_t->m_msgLHtmlTmpl);
            }
            break;
        case 1:
            if (_t->m_msgRHtmlTmpl != *reinterpret_cast< QString*>(_v)) {
                _t->m_msgRHtmlTmpl = *reinterpret_cast< QString*>(_v);
                Q_EMIT _t->signalMsgHtml(_t->m_msgRHtmlTmpl);
            }
            break;
        case 2:
            if (_t->m_msgRHtmlFile != *reinterpret_cast< QString*>(_v)) {
                _t->m_msgRHtmlFile = *reinterpret_cast< QString*>(_v);
                Q_EMIT _t->signalMsgHtml(_t->m_msgRHtmlFile);
            }
            break;
        case 3:
            if (_t->m_msgLHtmlFile != *reinterpret_cast< QString*>(_v)) {
                _t->m_msgLHtmlFile = *reinterpret_cast< QString*>(_v);
                Q_EMIT _t->signalMsgHtml(_t->m_msgLHtmlFile);
            }
            break;
        default: break;
        }
    }
}

const QMetaObject *MsgHtmlObj::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MsgHtmlObj::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MsgHtmlObjE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MsgHtmlObj::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MsgHtmlObj::signalMsgHtml(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MsgHtmlObj::FileMessageProgress(const QString & _t1, QString _t2, int _t3, QString _t4, int _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
namespace {
struct qt_meta_tag_ZN10WinMsgShowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10WinMsgShowE = QtMocHelpers::stringData(
    "WinMsgShow",
    "signal_file_drag",
    "",
    "fileName"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10WinMsgShowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

Q_CONSTINIT const QMetaObject WinMsgShow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWebEngineView::staticMetaObject>(),
    qt_meta_stringdata_ZN10WinMsgShowE.offsetsAndSizes,
    qt_meta_data_ZN10WinMsgShowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10WinMsgShowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WinMsgShow, std::true_type>,
        // method 'signal_file_drag'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void WinMsgShow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WinMsgShow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signal_file_drag((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (WinMsgShow::*)(QString );
            if (_q_method_type _q_method = &WinMsgShow::signal_file_drag; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *WinMsgShow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WinMsgShow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10WinMsgShowE.stringdata0))
        return static_cast<void*>(this);
    return QWebEngineView::qt_metacast(_clname);
}

int WinMsgShow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebEngineView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void WinMsgShow::signal_file_drag(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
