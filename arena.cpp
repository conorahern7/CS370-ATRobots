//
// Created by conor on 3/20/2018.
//

#include <QtWidgets>
#include "arena.h"
#include "atr2.h"
#include "atr2func.h"
#include <QPixmap>

arena::arena(atr2var* avtemp, QWidget *parent) : QWidget(parent)
{
    //QSignalMapper * signalMapper = new QSignalMapper;

    //connect(this, SIGNAL(doneDrawingRobots), this, SLOT(update()));
    //QObject::connect(signalMapper, SIGNAL(mapped(int*)), this, update_robot(int));
    //connect(this, SIGNAL(do_missile(mn)), this, update_missile(mn));

    setWindowTitle(QString::fromStdString("ATR2"));
    //resize(470, 470);
    setFixedSize(470, 470);

    av = avtemp;

    pix = new QPixmap(470, 470);
    pix->fill(Qt::black);
}

void arena::update_robot(int rn) {
    QPainter p(pix);

    //p.setRenderHint(QPainter::Antialiasing);

    if (av->robot[rn].shields_up) {
        p.setPen(QPen(atr2func::pascal_color(atr2func::robot_color_i(rn) & 7), 1));
        p.drawEllipse(av->robot[rn].tx[4] - atr2var::robot_scale,
                      av->robot[rn].ty[4] - atr2var::robot_scale,
                      atr2var::robot_scale * 2.0,
                      atr2var::robot_scale * 2.0);
    }
    if (av->robot[rn].selected) {
        p.setPen(QPen(atr2func::robot_color(rn), 6));
    } else {
        p.setPen(QPen(atr2func::robot_color(rn), 1));
    }
    p.drawLine(av->robot[rn].tx[1], av->robot[rn].ty[1], av->robot[rn].tx[2], av->robot[rn].ty[2]);
    p.drawLine(av->robot[rn].tx[2], av->robot[rn].ty[2], av->robot[rn].tx[3], av->robot[rn].ty[3]);
    p.drawLine(av->robot[rn].tx[3], av->robot[rn].ty[3], av->robot[rn].tx[1], av->robot[rn].ty[1]);
    if (av->robot[rn].selected) {
        p.setPen(QPen(atr2func::pascal_color(7), 3));
    } else {
        p.setPen(QPen(atr2func::pascal_color(7), 1));
    }
    p.drawLine(av->robot[rn].tx[4], av->robot[rn].ty[4], av->robot[rn].tx[5], av->robot[rn].ty[5]);
    p.setPen(QPen(atr2func::pascal_color(8), 1));
    if ((av->show_arcs) && (av->robot[rn].arc_count > 0)) {
        p.drawLine(av->robot[rn].tx[4], av->robot[rn].ty[4], av->robot[rn].tx[6], av->robot[rn].ty[6]);
        p.drawLine(av->robot[rn].tx[4], av->robot[rn].ty[4], av->robot[rn].tx[7], av->robot[rn].ty[7]);
        if (av->robot[rn].scanrange < 1500) {
            p.drawArc(av->robot[rn].tx[4] - (av->robot[rn].scanrange  * atr2var::screen_scale), //x
                      av->robot[rn].ty[4] - (av->robot[rn].scanrange  * atr2var::screen_scale), //y
                      (int)round(av->robot[rn].scanrange * atr2var::screen_scale * 2), //h
                      (int)round(av->robot[rn].scanrange * atr2var::screen_scale * 2), //w
                      av->robot[rn].startarc * 16, //startArc
                      (av->robot[rn].spanarc) * 16); //spanArc
        }
    }
    if ((av->show_arcs) && (av->robot[rn].sonar_count > 0)) {
        p.drawEllipse(av->robot[rn].tx[4] - (int)round(atr2var::max_sonar * atr2var::screen_scale),
                av->robot[rn].ty[4] - (int)round(atr2var::max_sonar * atr2var::screen_scale),
                (int)round(atr2var::max_sonar * atr2var::screen_scale * 2),
                (int)round(atr2var::max_sonar * atr2var::screen_scale * 2));
    }
}

void arena::update_missile(int mn) {
    QPainter p(pix);
    if (av->missile[mn].a == 1) {
        if (av->missile[mn].mult > av->robot[av->missile[mn].source].shotstrength) {
            if (av->robot[av->missile[mn].source].selected) {
                p.setRenderHint(QPainter::Antialiasing);
                p.setPen(QPen(atr2func::pascal_color(14 + (av->game_cycle & 1)), 3));
            } else {
                p.setPen(QPen(atr2func::pascal_color(14 + (av->game_cycle & 1)), 1));
            }
        } else {
            if (av->robot[av->missile[mn].source].selected) {
                p.setRenderHint(QPainter::Antialiasing);
                p.setPen(QPen(atr2func::pascal_color(15), 3));
            } else {
                p.setPen(QPen(atr2func::pascal_color(15), 1));
            }
        }

        p.drawLine((int)round(av->missile[mn].x * atr2var::screen_scale) + atr2var::screen_x,
                   (int)round(av->missile[mn].y * atr2var::screen_scale) + atr2var::screen_y,
                   (int)round(av->missile[mn].lx * atr2var::screen_scale) + atr2var::screen_x,
                   (int)round(av->missile[mn].ly * atr2var::screen_scale) + atr2var::screen_y);
    }

    else if (av->missile[mn].a == 2) {
        p.setPen(QPen(Qt::black, 8));
        p.drawEllipse(((int)round(av->missile[mn].x * atr2var::screen_scale) + atr2var::screen_x) - av->missile[mn].lrad,
                      ((int)round(av->missile[mn].y * atr2var::screen_scale) + atr2var::screen_y) - av->missile[mn].lrad,
                      av->missile[mn].lrad * 2, av->missile[mn].lrad * 2);

        if (av->missile[mn].a > 0) {
            p.setPen(QPen(atr2func::pascal_color(15), 1));
            p.drawEllipse(((int)round(av->missile[mn].x * atr2var::screen_scale) + atr2var::screen_x) - av->missile[mn].rad,
                          ((int)round(av->missile[mn].y * atr2var::screen_scale) + atr2var::screen_y) - av->missile[mn].rad,
                          av->missile[mn].rad * 2, av->missile[mn].rad * 2);
        }
    }
}

void arena::update_mine(int rn, int mn) {
    QPainter p(pix);

    p.setPen(QPen(atr2func::robot_color(rn), 1));
    p.drawLine((int)std::round(av->robot[rn].mine[mn].x * atr2var::screen_scale) + atr2var::screen_x,
               (int)std::round(av->robot[rn].mine[mn].y * atr2var::screen_scale) + atr2var::screen_y - 1,
               (int)std::round(av->robot[rn].mine[mn].x * atr2var::screen_scale) + atr2var::screen_x,
               (int)std::round(av->robot[rn].mine[mn].y * atr2var::screen_scale) + atr2var::screen_y + 1);
    p.drawLine((int)std::round(av->robot[rn].mine[mn].x * atr2var::screen_scale) + atr2var::screen_x + 1,
               (int)std::round(av->robot[rn].mine[mn].y * atr2var::screen_scale) + atr2var::screen_y,
               (int)std::round(av->robot[rn].mine[mn].x * atr2var::screen_scale) + atr2var::screen_x - 1,
               (int)std::round(av->robot[rn].mine[mn].y * atr2var::screen_scale) + atr2var::screen_y);
}

void arena::new_cycle() {
    pix->fill(Qt::black);
}

void arena::paintEvent(QPaintEvent *)
{
    //int side = qMin(width(), height());
    //QPainter p(this);
    //p->setRenderHint(QPainter::Antialiasing);
    //p->translate(width() / 2, height() / 2);
    //p->scale(side / 200.0, side / 200.0);

    QPainter p(this);

    p.drawPixmap(0, 0, *pix);
    //p.drawPixmap(0, 0, *pix[34]);
    //p.drawPixmap(0, 0, *pix[33]);
}

arena::~arena() {
    exit(0);
}
