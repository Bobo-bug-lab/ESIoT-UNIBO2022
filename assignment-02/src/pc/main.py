import sys
import time
import datetime
import threading
import serial
import serial.tools.list_ports
import PyQt5
from PyQt5 import QtCore, QtGui, QtWidgets, QtChart
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtChart import *


class MainWindow(QMainWindow):

    portList = []
    is_com_open = False
    com = None             # the object of COM

    is_app_closing = False        # indicate that the app is exiting

    preview_len = 100

    data_count = 0

    # signals, be used to update the GUI
    updateSignal_comportList = pyqtSignal()
    updateSignal_notices = pyqtSignal(str)
    updateSignal_label_time = pyqtSignal(str)
    updateSignal_dataPreview = pyqtSignal(str)

    def __init__(self, app):
        super(MainWindow, self).__init__()

        self.initWindow(self)

        # refresh ports before poping up the GUI
        initPortProcess = threading.Thread(target=self.comport_refresh)
        initPortProcess.setDaemon(True)
        initPortProcess.start()

        self.refresh_label_time_Thread = threading.Thread(
            target=self.refresh_label_time)
        self.refresh_label_time_Thread.setDaemon(True)
        self.refresh_label_time_Thread.start()

        self.refresh_com_data_Thread = threading.Thread(
            target=self.refresh_com_data)
        self.refresh_com_data_Thread.setDaemon(True)
        self.refresh_com_data_Thread.start()
        return

    def closeEvent(self, event):
        reply = QMessageBox.question(self, 'Exit?',
                                     "Exit?", QMessageBox.Yes |
                                     QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            self.is_app_closing = True
            time.sleep(0.11)
            event.accept()
        else:
            event.ignore()

    def __del__(self):
        if self.com != None:
            self.com.close()
        return

    def initWindow(self, Form):

        # Set the main window

        Form.setObjectName("MainWindow")
        Form.resize(1000, 500)
        Form.setMinimumSize(QtCore.QSize(1000, 500))
        Form.setMaximumSize(QtCore.QSize(1000, 500))
        Form.setWindowTitle("Smart Bridge Control Console")
        # Form.setStyleSheet("background-color: #FEFEDF")

        # Port selection

        self.label_com_state = QtWidgets.QLabel(Form)
        self.label_com_state.setGeometry(QtCore.QRect(10, 0, 380, 30))
        self.label_com_state.setTextFormat(QtCore.Qt.AutoText)
        self.label_com_state.setAlignment(
            QtCore.Qt.AlignLeading | QtCore.Qt.AlignLeft | QtCore.Qt.AlignVCenter)
        self.label_com_state.setText(
            "Port <font color=\"#8E4860\">Close</font>")

        self.combobox_comport = QtWidgets.QComboBox(Form)
        self.combobox_comport.setGeometry(QtCore.QRect(10, 30, 380, 30))
        self.updateSignal_comportList.connect(self.comport_updateCombobox)

        self.button_comport_refresh = QtWidgets.QPushButton(Form)
        self.button_comport_refresh.setGeometry(QtCore.QRect(10, 70, 185, 30))
        self.button_comport_refresh.setText("Refresh")
        self.button_comport_refresh.clicked.connect(self.comport_refresh)

        self.button_comport_switch = QtWidgets.QPushButton(Form)
        self.button_comport_switch.setGeometry(QtCore.QRect(205, 70, 185, 30))
        self.button_comport_switch.setText("OPEN")
        self.button_comport_switch.clicked.connect(self.comport_switch)

        # the state of LEDs and normal/pre-alarm/alarm situation

        self.label_on_the_states = QtWidgets.QLabel(Form)
        self.label_on_the_states.setGeometry(QtCore.QRect(400, 0, 130, 30))
        self.label_on_the_states.setTextFormat(QtCore.Qt.AutoText)
        self.label_on_the_states.setText("Current State")

        self.label_states = QtWidgets.QLabel(Form)
        self.label_states.setGeometry(QtCore.QRect(400, 20, 600, 90))
        self.label_states.setTextFormat(QtCore.Qt.AutoText)
        self.label_states.setAlignment(
            QtCore.Qt.AlignLeading | QtCore.Qt.AlignCenter | QtCore.Qt.AlignVCenter)
        self.label_states.setText(
            "<h1>Situation: <font color=\"#999999\">Disconnected</font></h1>" +
            "<h2>LEDs: " +
            "<font color=\"#999999\">LA(N/A) </font>" +
            "<font color=\"#999999\">LB(N/A) </font>" +
            "<font color=\"#999999\">LC(N/A) </font></h2>")

        # The chart to view the data

        self.plotchart_dataPreview = QtChart.QChartView(Form)
        self.plotchart_dataPreview.setGeometry(
            QtCore.QRect(390, 120, 610, 380))
        self.plotchart_dataPreview.setToolTip("Water Level")
        self.plotchart_dataPreview.setRenderHint(QPainter.Antialiasing)

        self.label_dataPreview = QtWidgets.QLabel(Form)
        self.label_dataPreview.setGeometry(QtCore.QRect(400, 100, 130, 30))
        self.label_dataPreview.setTextFormat(QtCore.Qt.AutoText)
        self.label_dataPreview.setText("Temporal Trend")

        self.time_axisX = QtChart.QValueAxis()
        self.time_axisX.setVisible(False)
        self.time_axisX.setMin(0)
        self.time_axisX.setMax(self.preview_len)
        self.value_axisY = QtChart.QValueAxis()
        self.value_axisY.setLabelFormat("%d")
        self.value_axisY.setRange(0, 2000)

        self.series = QtChart.QSplineSeries()
        self.series.setName("Water Level")
        self.series.setColor(QColor(255, 17, 17, 255))
        self.chart = QtChart.QChart()
        self.chart.addSeries(self.series)
        self.chart.addAxis(self.time_axisX, Qt.AlignBottom)
        self.chart.addAxis(self.value_axisY, Qt.AlignLeft)
        self.chart.legend().detachFromChart()
        self.series.attachAxis(self.time_axisX)
        self.series.attachAxis(self.value_axisY)
        self.plotchart_dataPreview.setChart(self.chart)

        self.updateSignal_dataPreview.connect(self.update_dataPreview)

        # Show the time
        self.label_time = QtWidgets.QLabel(Form)
        self.label_time.setGeometry(QtCore.QRect(800, 0, 190, 30))
        self.label_time.setTextFormat(QtCore.Qt.AutoText)
        self.label_time.setAlignment(
            QtCore.Qt.AlignRight | QtCore.Qt.AlignVCenter)
        self.label_time.setText('<font color="#0000FF">Initializing...</font>')
        self.updateSignal_label_time.connect(self.update_label_time)

        # Notices
        self.label_notices = QtWidgets.QLabel(Form)
        self.label_notices.setGeometry(QtCore.QRect(10, 100, 100, 30))
        self.label_notices.setTextFormat(QtCore.Qt.AutoText)
        self.label_notices.setText("Notices")

        self.textEdit_notices = QtWidgets.QTextEdit(Form)
        self.textEdit_notices.setGeometry(
            QtCore.QRect(10, 130, 380, 360))
        self.textEdit_notices.setReadOnly(True)
        self.textEdit_notices.setToolTip("some notices")
        self.updateSignal_notices.connect(self.update_notices)

        # show the GUI
        self.show()

        return

    def comport_refresh(self):
        self.prompt_print("Ports sanning...")
        try:
            self.portList = list(serial.tools.list_ports.comports())
            self.updateSignal_comportList.emit()
            self.prompt_print(
                "Scanned %d ports." % (len(self.portList)))

        except Exception as e:
            print("Met error in scanning ports, " + str(e))
            self.prompt_print(
                "Met error in scanning ports, " + str(e), color="#FF8848")

        return

    def comport_updateCombobox(self):
        self.combobox_comport.clear()
        for i in self.portList:
            self.combobox_comport.addItem(str(i[0]) + " " + str(i[1]))
        if len(self.portList) > 0:
            self.combobox_comport.setCurrentIndex(0)
            self.combobox_comport.setToolTip(str(self.portList[0]))
        return

    def comport_switch(self):
        time.sleep(0.1)
        if not self.is_com_open:
            # open the COM port
            try:
                portIndex = self.combobox_comport.currentIndex()
                self.com = serial.Serial(self.portList[portIndex][0],
                                         115200, timeout=0.5, write_timeout=0.5)

                time.sleep(0.5)

                self.is_com_open = True
                self.button_comport_refresh.setDisabled(True)
                self.combobox_comport.setDisabled(True)

                self.label_com_state.setText(
                    "Port <font color=\"#779ABF\">Opening</font>")
                self.button_comport_switch.setText("CLOSE")

                self.prompt_print("Opened COM port %s." %
                                  (str(self.portList[portIndex][0])))

            except Exception as e:
                if self.com != None:
                    self.com.close()
                self.prompt_print(
                    "Failed to open the COM port, " + str(e), color="#FF8848")

        else:
            # close the COM port
            try:
                self.label_com_state.setText(
                    "Port <font color=\"#8E4860\">Close</font>")
                self.button_comport_switch.setText("OPEN")
                self.prompt_print("COM port closed.")
                self.is_com_open = False
                self.button_comport_refresh.setDisabled(False)
                self.combobox_comport.setDisabled(False)

                self.com.close()

            except Exception as e:
                self.prompt_print(
                    "Failed to close the COM port, " + str(e), color="#FF8848")

        return

    def update_notices(self, content):
        if content != "":
            self.textEdit_notices.moveCursor(QTextCursor.End)
            self.textEdit_notices.insertHtml(content)
            self.textEdit_notices.moveCursor(QTextCursor.End)
        return

    def update_dataPreview(self, thisline):
        alarm_str = {
            "0": "<font color=\"#00FF00\">NORMAL</font>",
            "1": "<font color=\"#FF5555\">PRE-ALARM</font>",
            "2": "<font color=\"#FF0000\">ALARM</font>"
        }
        LA_str = {
            "0": "LA(<font color=\"#000000\">OFF</font>)",
            "1": "LA(<font color=\"#00FF00\">ON</font>)"
        }
        LB_str = {
            "0": "LB(<font color=\"#000000\">OFF</font>)",
            "1": "LB(<font color=\"#00FF00\">ON</font>)"
        }
        LC_str = {
            "0": "LC(<font color=\"#000000\">OFF</font>)",
            "1": "LC(<font color=\"#FF0000\">ON</font>)"
        }

        try:
            # print(thisline)
            alarm, waterlevel, LA, LB, LC = thisline[:-2].split(",")
            self.series.append(self.data_count, float(waterlevel))
            self.data_count += 1
            if self.data_count > self.preview_len:
                self.time_axisX.setMin(self.data_count - self.preview_len)
                self.time_axisX.setMax(self.data_count)

            self.label_states.setText(
                f"<h1>Situation: {alarm_str[alarm]}</h1>" +
                f"<h2>LEDs: {LA_str[LA]} {LB_str[LB]} {LC_str[LC]}</h2>")

        except Exception as e:
            print("Met error in update_dataPreview(): " + str(e))

    def update_label_time(self, content):
        self.label_time.setText(content)
        return

    def prompt_print(self, content, color="#00AAB0"):
        temp = (time.strftime(
            '<font color="' + color + '">%Y-%m-%d %H:%M:%S</font><br/>\n',
            time.localtime(time.time()))) + content + "<br/>\n"
        self.updateSignal_notices.emit(temp)

    def prompt_clear(self):
        self.textEdit_notices.clear()
        return

    def refresh_label_time(self):
        """an infinite loop to update the time"""
        try:
            while not self.is_app_closing:
                nowtime = time.strftime(
                    '%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
                self.updateSignal_label_time.emit(
                    '<font color="#00AAB0">%s</font>' % (nowtime))
                time.sleep(0.1)
        except Exception as e:
            print("Met an error in refresh_label_time(): " + str(e))

    def refresh_com_data(self):
        while True:
            if self.is_com_open:
                try:
                    thisline = self.com.readline()
                    thisline = thisline.decode("utf-8")
                    if thisline.count(",") == 4:
                        self.updateSignal_dataPreview.emit(thisline)

                except Exception as e:
                    print("Read COM port error, " + str(e))
                    if self.is_com_open:
                        self.prompt_print("Read COM port error, will retry after 10 seconds, the reason is: " +
                                          str(e), color="#FF8848")
                        time.sleep(10)
        return


if __name__ == '__main__':
    QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
    app = QApplication(sys.argv)
    mainWindow = MainWindow(app)
    sys.exit(app.exec_())
