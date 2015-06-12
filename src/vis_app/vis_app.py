#!/usr/bin/python
from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph.opengl as gl
import numpy as np
import copy

class Worker(QtCore.QObject):
	finished = QtCore.pyqtSignal()
	
	def __init__(self):
		QtCore.QObject.__init__(self)

	@QtCore.pyqtSlot()
	def listenForData(self):
		import socket
		import numpy as np
		UDP_IP = "127.0.0.1"
		UDP_PORT = 30001
		sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		sock.bind((UDP_IP, UDP_PORT))
		data, addr = sock.recvfrom(1024)
		print data
		dataSplit = data.split("#")
		redStr=dataSplit[0]
		greenStr=dataSplit[1]
		blueStr=dataSplit[2]
		print dataSplit
		while True:	
			global rPlot, gPLot, bPlot
			rPlot.setData(pos=np.matrix(redStr), color=(1.0,0.0,0.0,1.0), size=100, pxMode=True)
			gPlot.setData(pos=np.matrix(greenStr), color=(0.0,1.0,0.0,1.0), size=100, pxMode=True)
			bPlot.setData(pos=np.matrix(blueStr), color=(0.0,1.0,1.0,1.0), size=100, pxMode=True)
			print "RPLOT " + redStr
			print "GPLOT " + greenStr
			print "BPLOT " + blueStr
			data, addr = sock.recvfrom(1024)
			dataSplit = data.split("#")
			if dataSplit[0] != "":
				redStr+= ";"+dataSplit[0]
			if dataSplit[1] != "":
				greenStr+= ";"+dataSplit[1]
			if dataSplit[2] != "":
				blueStr+= ";"+dataSplit[2]
		finished.sen()

def makeGrid(size, sqX=100, sqY=100, sqZ=100):
	g = gl.GLGridItem()
	g.setSize(x=size, y=size)
	g.setSpacing(x=size/sqX, y=size/sqY, z=size)
	return g

app = QtGui.QApplication([])
import vis_ui as ui

window = ui.MainWindow()
window.show()

trackView = window.track
realView = window.real

trackView.opts['distance'] = 50000
realView.opts['distance'] = 50000
trackView.show()
realView.show()

import vis_mousefilter as vmf
myfilter = vmf.DopplegangerMouseFilter(window.track)
#offfilter = vmf.OffMouseFilter()
window.real.installEventFilter(myfilter)
#window.track.installEventFilter(offfilter)

grid = makeGrid(1000000)
realView.addItem(grid)
trackView.addItem(grid)

rPlot = gl.GLScatterPlotItem()
gPlot = gl.GLScatterPlotItem()
bPlot = gl.GLScatterPlotItem()
realView.addItem(rPlot)
trackView.addItem(gPlot)
trackView.addItem(bPlot)
md = gl.MeshData.sphere(8,8,10000)
mi = gl.GLMeshItem(meshdata=md, smooth=False, drawFaces=True, drawEdges=True, color=(1.0,1.0,0.0,0.02), edgeColor=(1.0,1.0,0.0,0.05))
mi.setGLOptions('additive')
mi2 = gl.GLMeshItem(meshdata=md, smooth=False, drawFaces=True, drawEdges=True, color=(1.0,1.0,0.0,0.02), edgeColor=(1.0,1.0,0.0,0.05))
mi2.setGLOptions('additive')
mi2.translate(20000,0,0)
realView.addItem(mi)
realView.addItem(mi2)
trackView.addItem(mi)
trackView.addItem(mi2)

thread = QtCore.QThread()
obj = Worker()
obj.moveToThread(thread)
obj.finished.connect(thread.quit)
thread.started.connect(obj.listenForData)
thread.finished.connect(app.exit)
thread.start()

## Start Qt event loop unless running in interactive mode.
if __name__ == '__main__':	
	import sys
	if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
		QtGui.QApplication.instance().exec_()
		

	
		
