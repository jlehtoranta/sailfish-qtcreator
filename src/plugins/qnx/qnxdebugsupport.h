/**************************************************************************
**
** Copyright (C) 2011 - 2013 Research In Motion
**
** Contact: Research In Motion (blackberry-qt@qnx.com)
** Contact: KDAB (info@kdab.com)
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef QNX_INTERNAL_QNXDEBUGSUPPORT_H
#define QNX_INTERNAL_QNXDEBUGSUPPORT_H

#include <projectexplorer/devicesupport/idevice.h>

#include <QObject>
#include <QString>

namespace Debugger { class DebuggerEngine; }
namespace ProjectExplorer {
class DeviceApplicationRunner;
class DeviceUsedPortsGatherer;
}

namespace Qnx {
namespace Internal {

class QnxRunConfiguration;

class QnxDebugSupport : public QObject
{
    Q_OBJECT
public:
    explicit QnxDebugSupport(QnxRunConfiguration *runConfig,
                             Debugger::DebuggerEngine *engine);

public slots:
    void handleDebuggingFinished();

private slots:
    void handleAdapterSetupRequested();

    void handleRemoteProcessStarted();
    void handleRemoteProcessFinished(bool success);
    void handleProgressReport(const QString &progressOutput);
    void handleRemoteOutput(const QByteArray &output);
    void handleError(const QString &error);
    void handlePortListReady();

private:
    void startExecution();
    void setFinished();

    QString executable() const;

    enum State {
        Inactive,
        GatheringPorts,
        StartingRemoteProcess,
        Debugging
    };

    const QString m_remoteExecutable;
    const QString m_commandPrefix;
    ProjectExplorer::IDevice::ConstPtr m_device;
    ProjectExplorer::DeviceApplicationRunner *m_runner;
    ProjectExplorer::DeviceUsedPortsGatherer * m_portsGatherer;
    Debugger::DebuggerEngine *m_engine;
    int m_pdebugPort;
    int m_qmlPort;

    bool m_useCppDebugger;
    bool m_useQmlDebugger;

    State m_state;
};

} // namespace Internal
} // namespace Qnx

#endif // QNX_INTERNAL_QNXDEBUGSUPPORT_H
