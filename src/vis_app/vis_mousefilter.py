from PyQt4.QtCore import * 
from PyQt4.QtGui import * 
import sys

class DopplegangerMouseFilter(QObject):
	def __init__(self, other):
		QObject.__init__(self)
		self.other=other
		
	def eventFilter(self, receiver, event):
		if event.type() in [QEvent.MouseMove, QEvent.Wheel]:
#			eventToSend = MyEvent(event)
#			QCoreApplication.sendEvent(self.other, eventToSend)
			print "here"
			QCoreApplication.sendEvent(self.other, event)			
			return super(DopplegangerMouseFilter,self).eventFilter(receiver, event)
		else:      
			#Call Base Class Method to Continue Normal Event Processing
			return super(DopplegangerMouseFilter,self).eventFilter(receiver, event)

class OffMouseFilter(QObject):
	def __init__(self):
		QObject.__init__(self)

	def eventFilter(self, receiver, event):
		if event.type() == MyEvent.type_:
			print event.type()
			return super(OffMouseFilter,self).eventFilter(receiver, event)
		else:      
			#Call Base Class Method to Continue Normal Event Processing
			return super(OffMouseFilter,self).eventFilter(receiver, event)

class MyEvent(QEvent):
	type_ = QEvent.registerEventType()

	def __init__(self, mouseEvent):
		QEvent.__init__(self, MyEvent.type_)
		self.mouseEvent = mouseEvent

