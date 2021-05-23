#ifndef KOMI_H
#define KOMI_H

#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QPair>


QT_BEGIN_NAMESPACE
namespace Ui { class komi; }
QT_END_NAMESPACE

class komi : public QMainWindow
{
    Q_OBJECT

public:
    komi(QWidget *parent = nullptr);
    ~komi();

private slots:

    void on_plus_clicked();

    void on_minus_clicked();

    void on_draw_clicked();

    void matrix();


    void on_result_clicked();

    void on_matrix_clicked();

private:
    Ui::komi *ui;

protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // KOMI_H
