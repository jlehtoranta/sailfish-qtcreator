/****************************************************************************
**
** Copyright (C) 2014 Jolla Ltd.
** Contact: http://jolla.com/
**
** This file is part of Qt Creator.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Digia.
**
****************************************************************************/

#ifndef MERSETTINGS_H
#define MERSETTINGS_H

#include <QtCore/QObject>

namespace Mer {
namespace Internal {

class MerSettings : public QObject
{
    Q_OBJECT
public:
    explicit MerSettings(QObject *parent = 0);
    ~MerSettings() override;

    static QObject *instance();

    static bool rpmValidationByDefault();

    static void setRpmValidationByDefault(bool byDefault);

signals:
    void rpmValidationByDefaultChanged(bool byDefault);

private:
    void read();
    void save();

private:
    static MerSettings *s_instance;
    bool m_rpmValidationByDefault;
};

} // Internal
} // Mer

#endif // MERSETTINGS_H
