/*
    Copyright (c) 2014, Lukas Holecek <hluk@email.cz>

    This file is part of CopyQ.

    CopyQ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CopyQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CopyQ.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCRIPTABLE_H
#define SCRIPTABLE_H

#include "scriptableproxy.h"

#include <QObject>
#include <QString>
#include <QScriptable>
#include <QScriptValue>

class ByteArrayClass;
class ClipboardBrowser;
class QScriptEngine;

class Scriptable : public QObject, protected QScriptable
{
    Q_OBJECT
    Q_PROPERTY(QString inputSeparator READ getInputSeparator WRITE setInputSeparator)
    Q_PROPERTY(QString currentPath READ getCurrentPath WRITE setCurrentPath)

public:
    Scriptable(ScriptableProxy *proxy, QObject *parent = NULL);

    void initEngine(QScriptEngine *engine, const QString &currentPath, const QByteArray &actionId);

    QScriptValue newByteArray(const QByteArray &bytes);

    QByteArray fromString(const QString &value) const;
    QString toString(const QScriptValue &value) const;
    bool toInt(const QScriptValue &value, int &number) const;
    QVariantMap toDataMap(const QScriptValue &value) const;

    /**
     * Return pointer to QByteArray or NULL.
     */
    QByteArray *getByteArray(const QScriptValue &value) const;

    QByteArray makeByteArray(const QScriptValue &value) const;

    /**
     * Set data for item converted from @a value.
     * Return true if data was successfuly converted and set.
     *
     * If mime starts with "text/" or isn't byte array the value is re-encoded
     * from local encoding to UTF8.
     */
    bool toItemData(const QScriptValue &value, const QString &mime, QVariantMap *data) const;

    QScriptValue applyRest(int first);

    const QString &getInputSeparator() const;
    void setInputSeparator(const QString &separator);

    const QString &getCurrentPath() const;
    void setCurrentPath(const QString &path);

    QString getFileName(const QString &fileName) const;

    QString arg(int i, const QString &defaultValue = QString());

    void throwError(const QString &errorMessage);

    void sendMessageToClient(const QByteArray &message, int exitCode);

    void sendWindowActivationCommandToClient(const QByteArray &message);

    QScriptEngine *engine() const { return m_engine; }

public slots:
    QScriptValue version();
    QScriptValue help();

    void show();
    void hide();
    void toggle();
    void menu();
    void exit();
    void disable();
    void enable();
    QScriptValue monitoring();

    void ignore();

    QScriptValue clipboard();
    QScriptValue selection();
    void copy();
    void paste();
    void pasteWithCtrlV();

    QScriptValue tab();
    void removetab();
    void renametab();

    QScriptValue length();
    QScriptValue size() { return length(); }
    QScriptValue count() { return length(); }

    void select();
    void next();
    void previous();
    void add();
    void insert();
    void remove();
    void edit();

    QScriptValue read();
    void write();
    QScriptValue separator();

    void action();
    void popup();

    void exporttab();
    void importtab();

    QScriptValue config();

    void eval();

    void currentpath();

    QScriptValue str(const QScriptValue &value);
    QScriptValue input();
    QScriptValue data(const QScriptValue &value);
    void print(const QScriptValue &value);
    void abort();

    void keys();

    QScriptValue selectitems();

    QScriptValue selectedtab();
    QScriptValue selecteditems();
    QScriptValue currentitem();

    QScriptValue index();

    QScriptValue escapeHTML();

    QScriptValue unpack();
    QScriptValue pack();

    QScriptValue getitem();
    void setitem();

    QScriptValue tobase64();
    QScriptValue frombase64();

    QScriptValue open();
    QScriptValue execute();

    QScriptValue currentWindowTitle();

public slots:
    void setInput(const QByteArray &bytes);

signals:
    void sendMessage(const QByteArray &message, int messageCode);
    void requestApplicationQuit();

private:
    QList<int> getRows() const;

    ScriptableProxy *m_proxy;
    QScriptEngine *m_engine;
    ByteArrayClass *m_baClass;
    QString m_inputSeparator;
    QString m_currentPath;
    QByteArray m_actionId;
    QScriptValue m_input;
};

#endif // SCRIPTABLE_H
