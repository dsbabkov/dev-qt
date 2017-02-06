#pragma once

#include <QWidget>
#include <memory>

class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QBoxLayout;
class QLineEdit;
class QSlider;
class QLabel;
class QSpinBox;
class QComboBox;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = {});
    ~MainWindow();

private:
    void setupHLayout() const;
    void setupVLayout() const;
    void setupGridLayout() const;
    void setupStackLayout();

    void setupWidgetsSizePolicy() const;

    void setupLayout(QLayout *layout) const;
    void addVerticalHorisontalBtns();
    void addExitBtn();

    void setupSpin();
    void setupSlider() const;
    void setupEdit();
    void setupLabel() const;

private:
    QHBoxLayout* mainLayout_;
    QHBoxLayout *hLayout_ ;
    QVBoxLayout *vLayout_ ;
    QGridLayout *gridLayout_;
    QVBoxLayout *stackLayoutWraper_;
    QComboBox *combo;
    QLineEdit *edit_;
    QSpinBox *spin_;
    QSlider *slider_;
    QLabel *label_;
};
