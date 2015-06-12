from PyQt4.QtCore import * 
from PyQt4.QtGui import * 
import sys
		
class DopplegangerControlFilter(QObject):
	def __init__(self, dop1, dop2):
		QObject.__init__(self)
		self.dop1 = dop1
		self.dop2 = dop2

	def eventFilter(self, receiver, event):
		if event.type() in [QEvent.KeyPress, QEvent.KeyRelease, QEvent.MouseButtonPress, QEvent.MouseMove, QEvent.Wheel]:
			QCoreApplication.sendEvent(self.dop1, event)
			QCoreApplication.sendEvent(self.dop2, event)
			return True
		return super(DopplegangerControlFilter,self).eventFilter(receiver, event)



