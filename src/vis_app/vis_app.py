#!/usr/bin/python
from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph.opengl as gl
import numpy as np
import copy

class Worker(QtCore.QObject):
	finished = QtCore.pyqtSignal()
	
	def __init__(self):
		QtCore.QObject.__init__(self)
		import socket
		import sys
		self.HOST = '' # Means all if
		self.PORT = 30001
 		# Udp socket
		try :
		    self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		    print 'Socket created'
		except socket.error, msg :
		    print 'Failed to create socket. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
		    sys.exit()
		# Bind socket to local host and port
		try:
			self.sock.bind((self.HOST, self.PORT))
		except socket.error , msg:
		    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
		    sys.exit()
		print 'Socket bind complete'
		self.initialised=False

	@QtCore.pyqtSlot()
	def plotLoop(self):
		if not self.initialised:
			print 'Plot not initialized'
			return
		while True:	
			global rPlot, gPLot, bPlot
			rPlot.setData(pos=np.matrix(self.redStr), color=(1.0,0.0,0.0,1.0), size=5, pxMode=True)
			gPlot.setData(pos=np.matrix(self.greenStr), color=(0.0,1.0,0.0,1.0), size=5, pxMode=True)
			bPlot.setData(pos=np.matrix(self.blueStr), color=(0.2,0.6,1.0,1.0), size=5, pxMode=True)
			data, addr = self.sock.recvfrom(1024)
			dataSplit = data.split("#")
			for data in dataSplit:
				print data
			if dataSplit[1] != "":
				self.redStr+= ";"+dataSplit[1]
			if dataSplit[2] != "":
				self.greenStr+= ";"+dataSplit[2]
			if dataSplit[3] != "":
				self.blueStr+= ";"+dataSplit[3]
			#print "RPLOT " + self.redStr
			#print "GPLOT " + self.greenStr
			#print "BPLOT " + self.blueStr
		finished.sen()

	def plotInit(self):
		data, addr = self.sock.recvfrom(1024)
		dataSplit = data.split("#")
		sensorData=dataSplit[0]
		self.redStr="0,0,0"
		self.greenStr="0,0,0"
		self.blueStr="0,0,0"
		global window
		for sensor in sensorData.split(";"):
			parameters = []
			for param in sensor.split(","):
				parameters.append(float(param))
			md = gl.MeshData.sphere(8,8,parameters[0])
			mi = gl.GLMeshItem(meshdata=md, smooth=False, drawFaces=True, drawEdges=True, color=(1.0,1.0,0.0,0.02), edgeColor=(1.0,1.0,0.0,0.05))
			mi.setGLOptions('additive')
			mi.translate(parameters[1], parameters[2], parameters[3])
			for view in [window.real, window.track]:
				view.addItem(mi)
		self.initialised=True

def makeGrid(size, sqX=100, sqY=100, sqZ=100):
	g = gl.GLGridItem()
	g.setSize(x=size, y=size)
	g.setSpacing(x=size/sqX, y=size/sqY, z=size)
	g.setGLOptions('additive')
	return g

app = QtGui.QApplication([])
import vis_ui as ui

window = ui.MainWindow()
window.show()

grid = makeGrid(1000000)
axisSize=30000
axis = gl.GLAxisItem(antialias=True)
axis.setSize(axisSize, axisSize, axisSize)

for view in [window.real, window.track]:
	view.opts['distance'] = 50000
	view.addItem(grid)
	view.addItem(axis)
	view.show()

import vis_controlfilter as vcf
controlfilter = vcf.DopplegangerControlFilter(window.real, window.track)
window.realMask.installEventFilter(controlfilter)
window.trackMask.installEventFilter(controlfilter)

null_matrix = np.matrix('0,0,0')
null_color = (0,0,0,0)
rPlot = gl.GLScatterPlotItem(pos=null_matrix, size=0, color=null_color)
rPlot.setGLOptions('additive')
gPlot = gl.GLScatterPlotItem(pos=null_matrix, size=0, color=null_color)
gPlot.setGLOptions('additive')
bPlot = gl.GLScatterPlotItem(pos=null_matrix, size=0, color=null_color)
bPlot.setGLOptions('additive')
window.real.addItem(rPlot)
window.real.addItem(bPlot)
window.track.addItem(gPlot)
window.track.addItem(bPlot)

thread = QtCore.QThread()
obj = Worker()
obj.plotInit()
obj.moveToThread(thread)
obj.finished.connect(thread.quit)
thread.started.connect(obj.plotLoop)
thread.finished.connect(app.exit)
thread.start()

## Start Qt event loop unless running in interactive mode.
if __name__ == '__main__':	
	import sys
	if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
		QtGui.QApplication.instance().exec_()
		

	
		
