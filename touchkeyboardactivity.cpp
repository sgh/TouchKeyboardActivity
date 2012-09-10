#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xdefs.h> // For Bool
#include <QtGui/QtGui>
#include <QtCore/QVector>

int be_verbose = 0;

struct XY {
	int x;
	int y;
};

class ActivityWidget : public QWidget {
	QVector<XY> _moves;
	QVector<XY> _presses;
	int _keypresses;

public:
	ActivityWidget() {
		setMouseTracking(true);
		// Mimmic showFullScreen with the exception that activateWindow() is not called since it
		// makes keyboardfocus misbehave when running without a window manager.
		ensurePolished();
		setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowMaximized)) | Qt::WindowFullScreen);
		show();
		update();
		_keypresses = 0;

		QPalette p(palette());
		p.setColor(QPalette::Background, Qt::black);
		setPalette(p);
	}

	virtual void 	keyPressEvent ( QKeyEvent * event ) {
		_keypresses++;
		update();
	}

	virtual void mousePressEvent ( QMouseEvent * event ) {
		XY e;
		e.x = event->x();
		e.y = event->y();
		_presses.append(e);
		if (_presses.count() > 1000)
			_presses.pop_front();
		printf("Press: (%d, %d)\n", e.x, e.y);
		update();
	}
	
	virtual void mouseMoveEvent ( QMouseEvent * event ) {
		XY e;
		e.x = event->x();
		e.y = event->y();
		_moves.append(e);
		if (_moves.count() > 10000)
			_moves.pop_front();
		printf("Move: (%d, %d)\n", e.x, e.y);
		update();
	}

	void paintEvent (QPaintEvent *) {
		bool first;
		QPainterPath path;
		QPainter qpainter (this);

		// Plot mouse movements
		qpainter.setPen(QColor(255, 0, 0));
		first = true;
		QVector<XY>::iterator it = _moves.begin();
		while (it != _moves.end()) {
			if (first) {
				path.moveTo((*it).x, (*it).y);
				first = false;
			} else
				path.lineTo((*it).x, (*it).y);
			it++;
		}
		qpainter.drawPath(path);

		// Plot mouse presses
		qpainter.setPen(QColor(0, 0, 127));
		qpainter.setBrush(QBrush(QColor(0, 0, 255),Qt::SolidPattern));
		it = _presses.begin();
		while (it != _presses.end()) {
			qpainter.drawEllipse((*it).x-10, (*it).y-10, 20, 20);
			it++;
		}

		qpainter.setPen(QColor(255, 255, 255));
		qpainter.drawText(10,height()/2, QString("Keypresses: %1").arg(_keypresses));

	}

};

int main(int argc, char* argv[]) {
	int opt;

	while ((opt = getopt(argc, argv, "hv")) != -1) {
		switch (opt) {
			case 'v':
				be_verbose = 1;
				break;
			case 'h':
			default: /* '?' */
					fprintf(stderr, "Usage: %s [option]]\n",argv[0]);
					fprintf(stderr, "   -v : Be verbose\n");
					fprintf(stderr, "   -h : Show this help\n");
					exit(EXIT_FAILURE);
		}
	}

	QApplication app(argc, argv);
	ActivityWidget activityl;
	
	return app.exec();
}
