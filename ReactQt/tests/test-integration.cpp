/**
 * Copyright (c) 2017-present, Status Research and Development GmbH.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include <QSignalSpy>
#include <QTest>
#include <QtQuick/QQuickView>

#include "reactbridge.h"
#include "reactredboxitem.h"
#include "reacttestcase.h"
#include "reacttestmodule.h"
#include "reactview.h"

class TestIntegration : public ReactTestCase {
    Q_OBJECT

private slots:
    INIT_TEST_CASE_DEFAULT(ReactTestCase)
    CLEANUP_TEST_CASE_DEFAULT(ReactTestCase)

    void testTestModuleMarkTestCompleted();
    void testJSExceptionReceived();
};

void TestIntegration::testTestModuleMarkTestCompleted() {
    loadQML(QUrl("qrc:/TestModuleTest.qml"));
    waitAndVerifyBridgeReady();

    ReactTestModule* testModule = bridge()->testModule();
    QVERIFY(testModule);
    QSignalSpy spy(testModule, &ReactTestModule::testCompleted);

    waitAndVerifyJsAppStarted();

    showView();
    waitAndVerifyCondition([&]() { return spy.count(); }, "Application running timeout");
}

void TestIntegration::testJSExceptionReceived() {
    loadJSBundle("TestJSException", "IntegrationTests/TestJSException");

    waitAndVerifyJsAppStarted();
    waitAndVerifyJSException("Exception on componentDidMount. File TestJSException.js");
}

QTEST_MAIN(TestIntegration)
#include "test-integration.moc"
